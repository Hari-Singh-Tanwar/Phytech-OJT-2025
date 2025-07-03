// Objective: Use one switch to cycle through three LEDs. The active LED should only be on while the switch is held down.

// Behavior:

//     The 1st press turns on LED 1.

//     The 2nd press turns on LED 2.

//     The 3rd press turns on LED 3.

//     All LEDs turn off when the switch is released.

// Bonus: Display the number of times the switch has been pressed.

// Input Pin (Switch): PB8

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

    // Set PA7, PA8, PA9 as output pins (LEDs)
    GPIOA->MODER |= GPIO_MODER_MODE7_0; // PA7 as output
    GPIOA->MODER |= GPIO_MODER_MODE8_0; // PA8 as output
    GPIOA->MODER |= GPIO_MODER_MODE9_0; // PA9 as output

    // Set PB8 as input (optional, reset state is input)
    GPIOB->MODER &= ~GPIO_MODER_MODE8; // PB8 as input

    // Enable pull-down resistor for PB8
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD8;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPD8_1; // Pull-down

    int count = 0;
    int prev_state = 0;

    while (1)
    {
        int curr_state = (GPIOB->IDR & GPIO_IDR_ID8) ? 1 : 0;

        // Detect rising edge (button press)
        if (curr_state && !prev_state)
        {
            count++;
            if (count > 3) count = 1;
        }

        // Control LEDs based on count, only while button is held
        if (curr_state)
        {
            if (count == 1)
                GPIOA->ODR = (GPIOA->ODR & ~(GPIO_ODR_OD7 | GPIO_ODR_OD8 | GPIO_ODR_OD9)) | GPIO_ODR_OD7;
            else if (count == 2)
                GPIOA->ODR = (GPIOA->ODR & ~(GPIO_ODR_OD7 | GPIO_ODR_OD8 | GPIO_ODR_OD9)) | GPIO_ODR_OD8;
            else if (count == 3)
                GPIOA->ODR = (GPIOA->ODR & ~(GPIO_ODR_OD7 | GPIO_ODR_OD8 | GPIO_ODR_OD9)) | GPIO_ODR_OD9;
        }
        else
        {
            // Turn off all LEDs when button is released
            GPIOA->ODR &= ~(GPIO_ODR_OD7 | GPIO_ODR_OD8 | GPIO_ODR_OD9);
        }

        prev_state = curr_state;
        delay(50); // Small delay for debouncing
    }
}