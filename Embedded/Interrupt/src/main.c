/* p6_1.c using SW0 interrupt
*
* User Switch B1 is used to generate interrupt through PC13. * The
user button is connected to PC13. It has a pull-up resitor * so PC13
stays high when the button is not pressed.
* When the button is pressed, PC13 becomes low.
* The falling-edge of PC13 (when switch is pressed) triggers an *
interrupt from External Interrupt Controller (EXTI).
* In the interrupt handler, the user LD2 is blinked twice. * It
serves as a crude way to debounce the switch.
* The green LED (LD2) is connected to PA5.
*
* This program was tested with Keil uVision v5.24a with DFP v2.11.0.
*/
#include "stm32f4xx.h"

// void delayMs(int n);

void delay(volatile uint16_t count)
{
    uint32_t i = count * 1000;
    while (i--)
    {
        __asm("nop");
    }
}

int main(void)
{
    __disable_irq();        /* global disable IRQs */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;      /* enable GPIOC clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;      /*enable GPIOA clock */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; /* enable SYSCFG clock*/

    /* configure PA5 for LED */
    GPIOA->MODER &= ~GPIO_MODER_MODE5_1; /* clear pin mode */
    GPIOA->MODER |= GPIO_MODER_MODE5_0; /* set pin to output mode */

    /* configure PC13 for push button interrupt */
    GPIOC->MODER &= ~GPIO_MODER_MODE13_1;  /* clear pin mode to input mode */
    GPIOC->MODER &= ~GPIO_MODER_MODE13_0;  /* clear pin mode to input mode */
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC; /* clear port selection for EXTI13 */
    // SYSCFG->EXTICR[3] |= 0x0020;  /* select port C for EXTI13 */
    EXTI->IMR |= EXTI_IMR_IM13; //0x2000;          /* unmask EXTI13 */
    EXTI->FTSR |= EXTI_FTSR_TR13;//0x2000;         /* select falling edge trigger */
    // NVIC->ISER[1] = 0x00000100; /* enable IRQ40 (bit 8 of ISER[1]) */
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    __enable_irq(); /* global enable IRQs */
    while (1)
    {
    }
}
void EXTI15_10_IRQHandler(void)
{
    GPIOA->BSRR = 0x00000020; /* turn on green LED */
    delay(250);
    GPIOA->BSRR = 0x00200000; /* turn off green LED */
    delay(250);
    GPIOA->BSRR = 0x00000020; /* turn on green LED */
    delay(250);
    GPIOA->BSRR = 0x00200000; /* turn off green LED */
    delay(250);
    EXTI->PR = EXTI_PR_PR13; /* clear interrupt pending flag */
}
/* 16 MHz SYSCLK */
// void delayMs(int n)
// {
//     int i;
//     for (; n > 0; n--)
//         for (i = 0; i < 3195; i++);
// }

