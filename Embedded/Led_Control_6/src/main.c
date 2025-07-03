// Objective: Use one switch to cycle through turning on three LEDs, where the LEDs remain in their state after the switch is released.

// Behavior:

//     The 1st press turns on LED 1.

//     The 2nd press turns on LED 2.

//     The 3rd press turns on LED 3.

//     The state of the LEDs does not change when the switch is released.

// Bonus: Display the number of times the switch has been pressed.

// Input Pin (Switch): PB8

// Output Pins (LEDs): PA7 (LED 1), PA8 (LED 2), PA9 (LED 3)


#include "stm32f4xx.h"

void delay(volatile uint16_t count)
{
    uint32_t i = count * 1000;
    while (i--)
    {
        __asm("nop");
    }
}

int main(){

    // Enable GPIOA and GPIOB clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable clock for GPIOB

    // Set PA7, PA8, PA9 as output pins (LEDs)
    GPIOA->MODER |= GPIO_MODER_MODE7_0; // PA7 as output
    GPIOA->MODER |= GPIO_MODER_MODE8_0; // PA8      
    GPIOA->MODER |= GPIO_MODER_MODE9_0; // PA9 as output



    while(1){
        // Read the state of the switch (PB8)
        int switch_state = (GPIOB->IDR & GPIO_IDR_ID8) ? 1 : 0;
        delay(300); // Debounce delay
        // Check if the switch is pressed
        if (switch_state) {
            // Cycle through LEDs based on the switch press
            static int led_state = 0; // 0: LED1, 1: LED2, 2: LED3
            led_state = (led_state + 1) % 3; // Cycle through 0, 1, 2

            // Turn on the corresponding LED
            GPIOA->ODR &= ~(GPIO_ODR_OD7 | GPIO_ODR_OD8 | GPIO_ODR_OD9); // Turn off all LEDs
            if (led_state == 0) {
                GPIOA->ODR |= GPIO_ODR_OD7; // Turn on LED1
            } else if (led_state == 1) {
                GPIOA->ODR |= GPIO_ODR_OD8; // Turn on LED2
            } else if (led_state == 2) {
                GPIOA->ODR |= GPIO_ODR_OD9; // Turn on LED3
            }
        } else {
            // If the switch is not pressed, keep the current LED state
            // No action needed here as LEDs remain in their state
        }
    }
}