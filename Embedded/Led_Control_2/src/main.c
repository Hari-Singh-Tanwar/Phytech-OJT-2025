/*
Objective: Write a program to control three separate LEDs with three switches, where each LED flashes on briefly when its corresponding switch is pressed.

Behavior:

    Pressing Switch 1 turns LED 1 on, then off.

    Pressing Switch 2 turns LED 2 on, then off.

    Pressing Switch 3 turns LED 3 on, then off.

Input Pins (Switches): PB8 (for LED 1), PB9 (for LED 2), PC9 (for LED 3)

Output Pins (LEDs): PA7 (LED 1), PA8 (LED 2), PA9 (LED 3)
*/

#include <stm32f446xx.h>

void delay(volatile uint16_t count)
{
    uint32_t i = count * 1000;
    while (i--)
    {
        __asm("nop");
    }
}

int main()
{
    // Enable GPIOA and GPIOB clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // Enable clock for GPIOB
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; // Enable clock for GPIOC

    // Set PA7, PA8, PA9 as output pins (LEDs)
    GPIOA->MODER |= GPIO_MODER_MODE7_0; // PA7 as output
    GPIOA->MODER |= GPIO_MODER_MODE8_0; // PA8 as output
    GPIOA->MODER |= GPIO_MODER_MODE9_0; // PA9 as output

    while (1)
    {
        if (GPIOB->IDR & GPIO_IDR_ID8)
        {                           // Check if Switch 1 is pressed
            GPIOA->ODR |= GPIO_ODR_OD7; // Turn on LED 1
            delay(1000);                 // Delay
            GPIOA->ODR &= ~GPIO_ODR_OD7; // Turn off LED 1
        }

        if (GPIOB->IDR & GPIO_IDR_ID9)
        {                           // Check if Switch 2 is pressed
            GPIOA->ODR |= GPIO_ODR_OD8; // Turn on LED 2
            delay(1000);                    // Delay
            GPIOA->ODR &= ~GPIO_ODR_OD8; // Turn off LED 2
        }

        if (GPIOC->IDR & GPIO_IDR_ID9)
        {                           // Check if Switch 3 is pressed
            GPIOA->ODR |= GPIO_ODR_OD9; // Turn on LED 3
            delay(1000 );                    // Delay
            GPIOA->ODR &= ~GPIO_ODR_OD9; // Turn off
        }
         delay(100);
    }
}