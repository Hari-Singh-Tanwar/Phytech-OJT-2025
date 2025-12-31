#!/usr/bin/env python3
"""
ESP32 UART to RuggedBoard LED Control using MRAA
Reads commands from ESP32 and controls 3 onboard LEDs
"""

import mraa
import time

# UART Configuration
UART_PORT = "/dev/ttyS3"  # MikroBUS UART
BAUD_RATE = 9600

# LED GPIO Pin Numbers (onboard LEDs)
LED_PINS = {
    1: 61,  # LED1 - PC13
    2: 62,  # LED2 - PC17
    3: 63   # LED3 - PC19
}

class UARTLEDController:
    def __init__(self):
        """Initialize MRAA for UART and GPIO"""
        print("===================================")
        print("RuggedBoard LED Controller via UART")
        print("===================================\n")
        
        # Initialize MRAA
        mraa.init()
        print("MRAA initialized")
        
        # Initialize UART
        self.init_uart()
        
        # Initialize LED GPIOs
        self.init_leds()
    
    def init_uart(self):
        """Initialize UART using MRAA"""
        try:
            print("\nOpening UART port {}...".format(UART_PORT))
            self.uart = mraa.Uart(UART_PORT)
            self.uart.setBaudRate(BAUD_RATE)
            self.uart.setMode(8, mraa.UART_PARITY_NONE, 1)
            self.uart.setFlowcontrol(False, False)
            print("UART opened at {} baud".format(BAUD_RATE))
        except Exception as e:
            print("Failed to initialize UART: {}".format(e))
            exit(1)
    
    def init_leds(self):
        """Initialize LED GPIOs using MRAA"""
        print("\nInitializing LEDs...")
        
        try:
            # Initialize LED1
            self.led1 = mraa.Gpio(LED_PINS[1])
            self.led1.dir(mraa.DIR_OUT)
            self.led1.write(1)  # Turn OFF (active low)
            print("LED1 (GPIO77) initialized")
            
            # Initialize LED2
            self.led2 = mraa.Gpio(LED_PINS[2])
            self.led2.dir(mraa.DIR_OUT)
            self.led2.write(1)  # Turn OFF (active low)
            print("LED2 (GPIO81) initialized")
            
            # Initialize LED3
            self.led3 = mraa.Gpio(LED_PINS[3])
            self.led3.dir(mraa.DIR_OUT)
            self.led3.write(1)  # Turn OFF (active low)
            print("LED3 (GPIO83) initialized")
            
            print("All LEDs initialized\n")
            
        except Exception as e:
            print("Failed to initialize LEDs: {}".format(e))
            exit(1)
    
    def control_led(self, led_num, state):
        """Control LED based on command"""
        try:
            # Active low: 0=ON, 1=OFF
            value = 0 if state == "ON" else 1
            
            if led_num == 1:
                self.led1.write(value)
                print("LED1 turned {}".format(state))
            elif led_num == 2:
                self.led2.write(value)
                print("LED2 turned {}".format(state))
            elif led_num == 3:
                self.led3.write(value)
                print("LED3 turned {}".format(state))
            else:
                print("Invalid LED number: {}".format(led_num))
        
        except Exception as e:
            print("Error controlling LED{}: {}".format(led_num, e))
    
    def parse_command(self, command):
        """Parse command: LED1:ON, LED1:OFF, LED2:ON, etc."""
        command = command.strip()
        
        if not command:
            return
        
        try:
            # Expected format: "LED1:ON" or "LED1:OFF"
            if "LED" in command and ":" in command:
                parts = command.split(":")
                
                # Extract LED number
                led_part = parts[0].replace("LED", "").strip()
                led_num = int(led_part)
                
                # Extract state
                state = parts[1].strip().upper()
                
                if state in ["ON", "OFF"]:
                    self.control_led(led_num, state)
                else:
                    print("Invalid state: {}".format(state))
            else:
                print("Invalid command format: {}".format(command))
        
        except Exception as e:
            print("Error parsing command '{}': {}".format(command, e))
    
    def run(self):
        """Main loop to receive and process UART data"""
        print("Waiting for commands from ESP32...")
        print("Expected format: LED1:ON, LED2:OFF, etc.\n")
        
        buffer = ""
        
        try:
            while True:
                # Check if data is available
                if self.uart.dataAvailable():
                    # Read available data
                    data = self.uart.readStr(64)
                    
                    if data:
                        # Add to buffer
                        buffer += data
                        
                        # Process complete lines (commands end with newline)
                        while '\n' in buffer:
                            line, buffer = buffer.split('\n', 1)
                            line = line.strip()
                            
                            if line:
                                print("Received: {}".format(line))
                                self.parse_command(line)
                
                # Small delay to prevent CPU overload
                time.sleep(0.01)
        
        except KeyboardInterrupt:
            print("\n\nShutting down...")
            self.cleanup()
    
    def cleanup(self):
        """Clean up resources"""
        print("Turning off all LEDs...")
        try:
            self.led1.write(1)
            self.led2.write(1)
            self.led3.write(1)
            print("All LEDs turned OFF")
        except:
            pass

def main():
    controller = UARTLEDController()
    controller.run()

if __name__ == "__main__":
    main()
