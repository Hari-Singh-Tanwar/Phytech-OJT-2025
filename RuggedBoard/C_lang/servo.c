#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

// Define sysfs paths for PWM control on Linux (PWM for servo control)
char export_path[] = "/sys/class/pwm/pwmchip0/export";         // Path to export PWM channel
char pwm_periods[] = "/sys/class/pwm/pwmchip0/pwm1/period";    // Path to set PWM period (20ms for servo)
char pwm_enable[] = "/sys/class/pwm/pwmchip0/pwm1/enable";     // Path to enable/disable PWM
char duty_cycle[] = "/sys/class/pwm/pwmchip0/pwm1/duty_cycle"; // Path to set duty cycle

// GPIO definitions for switch control
#define GPIO_EN "/sys/class/gpio/export"
#define SW_DIR "/sys/class/gpio/PC12/direction"
#define SW_VAL "/sys/class/gpio/PC12/value"

// Servo position definitions (in nanoseconds for 20ms period)
#define SERVO_PERIOD 20000000      // 20ms period for standard servo
#define SERVO_0_DEG 1000000        // 1ms pulse width for 0 degrees
#define SERVO_180_DEG 2000000      // 2ms pulse width for 180 degrees

int sw_fd;
int servo_position = 0; // 0 = 0 degrees, 1 = 180 degrees

// Initialize GPIO switch
int sw_init(int sw_num)
{
    char sw_buf[10];
    int fd;
    
    // Export GPIO pin
    fd = open(GPIO_EN, O_WRONLY);
    if (fd < 0)
    {
        printf("Unable to open the file %s\n", GPIO_EN);
        return -1;
    }
    sprintf(sw_buf, "%d", sw_num);
    write(fd, sw_buf, strlen(sw_buf));
    close(fd);
    
    usleep(100000); // Wait for export to complete
    
    // Set GPIO direction as input
    fd = open(SW_DIR, O_WRONLY);
    if (fd < 0)
    {
        printf("Unable to open direction file\n");
        return -1;
    }
    write(fd, "in", 2);
    close(fd);
    
    // Open GPIO value file for reading
    sw_fd = open(SW_VAL, O_RDONLY);
    if (sw_fd < 0)
    {
        printf("Unable to open value file\n");
        return -1;
    }
    
    return 0;
}

// Read switch state
int read_switch()
{
    char value;
    lseek(sw_fd, 0, SEEK_SET); // Reset file pointer to beginning
    read(sw_fd, &value, 1);
    return (value == '0') ? 0 : 1; // Return 0 for pressed, 1 for not pressed
}

int main(int argc, char **argv)
{
    int sw_num = 76;
    int fd;
    char duty_str[20];
    int last_switch_state = 1;
    int current_switch_state;
    
    printf("Servo Control Program\n");
    printf("Press switch to toggle between 0° and 180°\n");
    
    // Initialize switch
    if (sw_init(sw_num) < 0)
    {
        printf("Switch initialization failed\n");
        return -1;
    }
    
    // Export PWM channel 1
    fd = open(export_path, O_WRONLY);
    if (fd < 0)
        perror("export path error");
    write(fd, "1", 2);
    close(fd);
    
    usleep(100000); // Wait for PWM export
    
    // Set PWM period to 20ms (standard for servos)
    fd = open(pwm_periods, O_WRONLY);
    if (fd < 0)
        perror("period error");
    sprintf(duty_str, "%d", SERVO_PERIOD);
    write(fd, duty_str, strlen(duty_str));
    close(fd);
    
    // Set initial duty cycle to 0 degrees
    fd = open(duty_cycle, O_WRONLY);
    if (fd < 0)
        perror("duty cycle error");
    sprintf(duty_str, "%d", SERVO_0_DEG);
    write(fd, duty_str, strlen(duty_str));
    close(fd);
    
    // Enable PWM
    fd = open(pwm_enable, O_WRONLY);
    if (fd < 0)
        perror("enable error");
    write(fd, "1", 2);
    close(fd);
    
    printf("Servo initialized at 0 degrees\n");
    
    // Main loop - monitor switch and toggle servo position
    while (1)
    {
        current_switch_state = read_switch();
        
        // Detect switch press (transition from high to low)
        if (last_switch_state == 1 && current_switch_state == 0)
        {
            // Toggle servo position
            servo_position = !servo_position;
            
            // Open duty cycle file and set new position
            fd = open(duty_cycle, O_WRONLY);
            if (fd >= 0)
            {
                if (servo_position == 0)
                {
                    sprintf(duty_str, "%d", SERVO_0_DEG);
                    printf("Moving servo to 0 degrees\n");
                }
                else
                {
                    sprintf(duty_str, "%d", SERVO_180_DEG);
                    printf("Moving servo to 180 degrees\n");
                }
                write(fd, duty_str, strlen(duty_str));
                close(fd);
            }
            
            usleep(200000); // Debounce delay (200ms)
        }
        
        last_switch_state = current_switch_state;
        usleep(50000); // Poll switch every 50ms
    }
    
    close(sw_fd);
    return 0;
}