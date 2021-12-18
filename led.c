
#include "stm32g0xx.h"

#define LEDDELAY    1000000

void delay(volatile uint32_t);

int main(void) {
    
    /* Enable GPIOB clock */
    RCC->IOPENR |= (1U << 1);
    /* Setup PB2 as output */
    GPIOB->MODER &= ~(3U << 4);
    GPIOB->MODER |= (1U << 4);
    /* Turn on LED */
    GPIOB->ODR |= (1U << 2);

    while(1) {
        delay(LEDDELAY);
        /* Toggle LED */
        GPIOB->ODR ^= (1U << 2);
    }
    return 0;
}
void delay(volatile uint32_t s) {
    for(; s>0; s--);
}