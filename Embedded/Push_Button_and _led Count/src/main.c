#include <stm32f446xx.h>

void delay(volatile uint16_t count)
{
    uint32_t i = count * 1000;
    while (i--)
    {
        __asm("nop");
    }
}

void toggle_led(uint8_t count)
{
    for (uint8_t i = 0; i < count; i++)
    {
        GPIOA->ODR |= GPIO_ODR_OD5;
        delay(1000);
        GPIOA->ODR &= ~GPIO_ODR_OD5;
        delay(1000);
    }
}

int main(void)
{
    uint8_t count = 0;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN;
    GPIOA->MODER |= GPIO_MODER_MODE5_0; 

    while (1)
    {
        if (!(GPIOC->IDR & GPIO_IDR_ID13))
        {
            count++;
            if (count > 3)
            {
                count = 1;
            }
            toggle_led(count);
            delay(300); 
        }
        else{
            GPIOA->ODR &= ~GPIO_ODR_OD5;
        }
    }
}