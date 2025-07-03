// Objective: Write a program where switches cumulatively turn on a series of LEDs.

// Behavior:

//     Pressing Switch 1 turns on LED 1.

//     Pressing Switch 2 turns on LED 1 and LED 2.

//     Pressing Switch 3 turns on LED 1, LED 2, and LED 3.

// Input Pins (Switches): PB8 (Switch 1), PB9 (Switch 2), PC9 (Switch 3)

// Output Pins (LEDs): PA7 (LED 1), PA8 (LED 2), PA9 (LED 3)

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
        {                                // Check if Switch 1 is pressed
            GPIOA->ODR |= GPIO_ODR_OD7;  // Turn on LED 1
            GPIOA->ODR &= ~GPIO_ODR_OD8; // Turn on LED 2            // Check if Switch 3 is pressed
            GPIOA->ODR &= ~GPIO_ODR_OD9; // Turn on LED 3
            delay(300);
        }

        if (GPIOB->IDR & GPIO_IDR_ID9)
        {                               // Check if Switch 2 is pressed
            GPIOA->ODR |= GPIO_ODR_OD7; // Turn on LED 1
            GPIOA->ODR |= GPIO_ODR_OD8; // Turn on LED 2
            GPIOA->ODR &= ~GPIO_ODR_OD9; // Turn on LED 3
            delay(300);
        }

        if (GPIOC->IDR & GPIO_IDR_ID9)
        {
            GPIOA->ODR |= GPIO_ODR_OD7; // Turn on LED 1
            GPIOA->ODR |= GPIO_ODR_OD8; // Turn on LED 2            // Check if Switch 3 is pressed
            GPIOA->ODR |= GPIO_ODR_OD9; // Turn on LED 3
            delay(300);
        }
        delay(100);
    }
}