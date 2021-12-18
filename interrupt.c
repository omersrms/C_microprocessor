
#include "stm32g0xx.h"
int count=0;
int block=1000000; // default  1 sec
void SysTick_Handler(void){
    GPIOA->ODR ^= (1U << 7);
    if(count==block){
    GPIOA->BRR |= (1U << 7);
    delay_ms(count);
    GPIOA->ODR |= (1U << 7);
	SysTick->VAL = 0;
	count=0;
    }
    count++;
}

int main(void) {
	/* Enable GPIOA clock /  / Enable GPIOB clock */
	RCC->IOPENR |= (3U << 0);
	/* Setup PA7 as output */
	GPIOA->MODER &= ~(3U << 2*7);
	GPIOA->MODER |= (1U << 2*7);
	/* Clear led*/
	GPIOA->BRR |= (1U << 7);
	   SystemCoreClockUpdate();
	   SysTick_Config(SystemCoreClock / 1000); // 1ms

    while(1) {
    block=1000000;  // block time 1 second
    }
    return 0;
}
void delay_ms(volatile uint32_t s) {
    for(; s>0; s--);
}
