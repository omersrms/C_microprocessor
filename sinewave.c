
#include "stm32g0xx.h"

volatile uint32_t counter_t = 0;

const uint32_t sin_table[128] = {
512, 537, 562, 587, 612, 637, 661, 685, 709, 732, 754, 776, 798, 818, 838,
857, 875, 893, 909, 925, 939, 952, 965, 976, 986, 995, 1002, 1009, 1014, 1018,
1021, 1023, 1023, 1022, 1020, 1016, 1012, 1006, 999, 990, 981, 970, 959, 946, 932,
917, 901, 884, 866, 848, 828, 808, 787, 765, 743, 720, 697, 673, 649, 624,
600, 575, 549, 524, 499, 474, 448, 423, 399, 374, 350, 326, 303, 280, 258,
236, 215, 195, 175, 157, 139, 122, 106, 91, 77, 64, 53, 42, 33, 24,
17, 11, 7, 3, 1, 0, 0, 2, 5, 9, 14, 21, 28, 37, 47,
58, 71, 84, 98, 114, 130, 148, 166, 185, 205, 225, 247, 269, 291, 314,
338, 362, 386, 411, 436, 461, 486, 511
};
void TIM3_IRQHandler(){
TIM3->SR &= ~(1U<<0);
TIM3->SR &= ~(1U<<1);
}
void TIM2_IRQHandler(){
TIM3->ARR=sin_table[counter_t];
	counter_t++;
	if(counter_t>128){
		counter_t = 0;
	}
TIM3->EGR |= (1U<<0);
TIM2->SR &= ~(1U<<0);
TIM2->SR &= ~(1U<<1);
}
void InitTimer(){
RCC->APBENR1 |=(1U<<1);
TIM3->CR1=0;
TIM3->CR1 |=(1<<7);
TIM3->CNT =0;
TIM3->PSC=0;
TIM3->ARR=(8000);       // frekans artsın istiyorsan azalt
TIM3->DIER |=(1<<0);
TIM3->CCMR1 |=(1<<3);
TIM3->CCMR1 &= ~ (1u<<16); //0
TIM3->CCMR1 |=(1u<<6); //1
TIM3->CCMR1 |= (1u<<5); //1
TIM3->CCMR1 &= ~(1u<<4); // 0
TIM3->CCER |=(1<<0);// (capture compare 1) enable
TIM3->CCR1 =255;
//TIM3->AF1 |=(1<<14); //TİM3 af1 register ertsel comp1 output(?)
TIM3->EGR |= (1<<0); // update genration
TIM3->CR1 |= (1<<0);
NVIC_SetPriority(TIM3_IRQn,2);
NVIC_EnableIRQ(TIM3_IRQn);
}
void InitTimer2(){
RCC->APBENR1 |=(1U<<0);
TIM2->CR1=0;
TIM2->CNT =0;
TIM2->PSC=0;
TIM2->ARR=(10000);      // frekans artsın istiyorsan azalt
TIM2->DIER |=(1<<0);
TIM2->CR1 |= (1<<0);
NVIC_SetPriority(TIM2_IRQn,1);
NVIC_EnableIRQ(TIM2_IRQn);
}
void SpeakerInit(void){
/* Enable GPIOB and GPIOA clock */
RCC->IOPENR |= (3U << 0);
/* Setup PA6 as alternate function */
GPIOA->MODER &= ~(3U << 2*6); //PA6 RESET
GPIOA->MODER |= (2U<< 2*6) ; //PA6 SET as alternate function
GPIOA->AFR[0] &= ~(0xFU<<4*6); //reset the AF1
GPIOA->AFR[0] |= (1<<4*6);// AF1 ---- PA6
}

int main(void){
SystemCoreClockUpdate();
InitTimer();
InitTimer2();
SpeakerInit();

while(1){
}
return 0;
}

