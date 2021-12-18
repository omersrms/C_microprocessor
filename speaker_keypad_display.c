
#include "stm32g0xx.h"

void clearSSD		( void );
void setSSD			( int );

void clearRowsKeypad( void );
void setRowsKeypad  ( void );
int tone=0;
int i,j,k,l,tt,temp1,temp2,temp3,count1,count2,count3,mode;
int a1,a2,a3,a4,f1,f2,f3,f4,dotpos1,dotpos2;
int active=0;
int A_SAVE=0;
int F_SAVE=0;
int f_tim=128000;
int a_tim=3.3;
count2=0;
count3=0;
mode=3;
float amplitude=1;
float frequency=1000;
void EXTI0_1_IRQHandler(void){ // interrupt from PB0
	clearRowsKeypad();
GPIOA->ODR ^= (1U << 8); //PA8
if ((GPIOB->IDR >> 0) & 1 ) { // read PB0
shift(10);
delay(500000);
}
GPIOA->ODR ^= (1U << 8); //PA8

	GPIOB->ODR ^= (1U << 9); // PB9
	if ((GPIOB->IDR >> 0) & 1){
		//9
		shift(9);
		delay(500000);
	}
	GPIOB->ODR ^= (1U << 9); // PB9

	GPIOB->ODR ^= (1U << 5); // PB5
	if ((GPIOB->IDR >> 0) & 1){
		//6
		shift(6);
		delay(500000);
	}
	GPIOB->ODR ^= (1U << 5); // PB5

	GPIOB->ODR ^= (1U << 4); // PB4
	if ((GPIOB->IDR >> 0) & 1){
		//3
		shift(3);
		delay(500000);
	}
	GPIOB->ODR ^= (1U << 4); // PB4

	EXTI->RPR1 |= (1U << 0); // Clear interrupt flag
	setRowsKeypad();
}

void EXTI2_3_IRQHandler(void){ // interrupt from PB2
	clearRowsKeypad();

	GPIOA->ODR ^= (1U << 8); // PA8
		if ((GPIOB->IDR >> 2) & 1){
		//0
		shift(0);			//
		delay(500000);
			}
		GPIOA->ODR ^= (1U << 8); // PA8

		GPIOB->ODR ^= (1U << 9); // PB9
		if ((GPIOB->IDR >> 2) & 1){
			//8
			shift(8);
			delay(500000);
		}
		GPIOB->ODR ^= (1U << 9); // PB9

		GPIOB->ODR ^= (1U << 5); // PB5
		if ((GPIOB->IDR >> 2) & 1){
			//5
			shift(5);
			delay(500000);
		}
		GPIOB->ODR ^= (1U << 5); // PB5

		GPIOB->ODR ^= (1U << 4); // PB4
		if ((GPIOB->IDR >> 2) & 1){
			//2
			shift(2);
			delay(500000);
		}
		GPIOB->ODR ^= (1U << 4); // PB4

		EXTI->RPR1 |= (1U << 2); // Clear interrupt flag
	setRowsKeypad();
}

void EXTI4_15_IRQHandler(void){
if ( (EXTI->RPR1 >> 8) & 1 ) {
	clearRowsKeypad();

GPIOA->ODR ^= (1U << 8); //PA8
if ((GPIOB->IDR >> 8) & 1 ) { // read PB8

shift(15);
}
GPIOA->ODR ^= (1U << 8); //PA8

		GPIOB->ODR ^= (1U << 9); // PB9
		if ((GPIOB->IDR >> 8) & 1){
			//7
			shift(7);
			delay(500000);
		}
		GPIOB->ODR ^= (1U << 9); // PB9

		GPIOB->ODR ^= (1U << 5); // PB5
		if ((GPIOB->IDR >> 8) & 1){
			//4
			shift(4);
			delay(500000);
		}
		GPIOB->ODR ^= (1U << 5); // PB5

		GPIOB->ODR ^= (1U << 4); // PB4
		if ((GPIOB->IDR >> 8) & 1){
			//1
			shift(1);
			delay(500000);
		}
		GPIOB->ODR ^= (1U << 4); // PB4


	EXTI->RPR1 |= (1U << 8); // Clear interrupt flag
		setRowsKeypad();
   }
if ( (EXTI->RPR1 >> 9) & 1 ) {
clearRowsKeypad();
GPIOA->ODR ^= (1U << 8); //PA8
if ((GPIOA->IDR >> 9) & 1 ) { // read PA9
shift(11);
delay(500000); 
}
GPIOA->ODR ^= (1U << 8); //PA8
GPIOB->ODR ^= (1U << 9); //PB9
if ((GPIOA->IDR >> 9) & 1 ) { // read PA9
shift(12);
delay(500000);
}
GPIOB->ODR ^= (1U << 9); //PB9
GPIOB->ODR ^= (1U << 5); //PB5
if ((GPIOA->IDR >> 9) & 1 ) { // read PA9
shift(13);
delay(100000);
}
GPIOB->ODR ^= (1U << 5); //PB5
GPIOB->ODR ^= (1U << 4); //PB4
if ((GPIOA->IDR >> 9) & 1 ) { // read PA9
shift(14);
delay(100000);
}
GPIOB->ODR ^= (1U << 4); //PB4
EXTI->RPR1 |= (1U << 9);
setRowsKeypad();
}
}


void TIM3_IRQHandler(void){
TIM3->SR &= ~(1U<<0);
TIM3->SR &= ~(1U<<1);
}

void TIM2_IRQHandler(void) {
    // update duty (CCR2)

    TIM3->ARR=tone;

TIM3->EGR |= (1U<<0);
    // Clear update status register
    TIM2->SR &= ~(1U << 0);
    TIM2->SR &= ~(1U<<1);
}

int main(void) {

	/*Enable GPIOA clock */
	RCC->IOPENR |= (1U << 0);

	/*Enable GPIOB clock */
	RCC->IOPENR |= (1U << 1);

//ssd PB6 PB7 PB1 PA10 output
    GPIOA->MODER &= ~(3U << 2*10);
    GPIOA->MODER |=  (1U << 2*10);
    GPIOB->MODER &= ~(3U << 2*6);
    GPIOB->MODER |=  (1U << 2*6);
    GPIOB->MODER &= ~(3U << 2*7);
    GPIOB->MODER |=  (1U << 2*7);
    GPIOB->MODER &= ~(3U << 2*1);
    GPIOB->MODER |=  (1U << 2*1);

	/* Setup PA8, PB9, PB5, PB4 as output (rows) */
	GPIOA->MODER &= ~(3U << 2*8);
	GPIOA->MODER |=  (1U << 2*8); // PA8 is output ( 17-16 )

	GPIOB->MODER &= ~(3U << 2*9);
	GPIOB->MODER |=  (1U << 2*9); // PB9 is output ( 19-18 )

	GPIOB->MODER &= ~(3U << 2*5);
	GPIOB->MODER |=  (1U << 2*5); // PB5 is output ( 11-10 )

	GPIOB->MODER &= ~(3U << 2*4);
	GPIOB->MODER |=  (1U << 2*4); // PB4 is output ( 09-08 )



	/* Setup PB0, PB2, PB8 as input (colums) */
	GPIOB->MODER &= ~(3U << 2*0); // PB0 is output ( 01-00 )
	GPIOB->PUPDR |=  (2U << 2*0); // Pull down mode

	GPIOB->MODER &= ~(3U << 2*2); // PB2 is output ( 05-04 )
	GPIOB->PUPDR |=  (2U << 2*2); // Pull down mode

	GPIOB->MODER &= ~(3U << 2*8); // PB8 is output ( 17-16 )
	GPIOB->PUPDR |=  (2U << 2*8); // Pull down mode

 GPIOA->MODER &= ~(3U << 2*9); // PA9 D5
 GPIOA->PUPDR |= (2U << 2*9);

	/* Setup interrupts for inputs */
	EXTI->EXTICR[2] |= (0U << 8*1); // PA9
	EXTI->EXTICR[0] |= (1U << 0);    // PB0
	EXTI->EXTICR[0] |= (1U << 8*2);  // PB2
	EXTI->EXTICR[2] |= (1U << 0);    // PB8

	/* Rising Edge */
	EXTI->RTSR1 |= (1U << 9); // 9th pin
	EXTI->RTSR1 |= (1U << 0);  // 0th pin
	EXTI->RTSR1 |= (1U << 2);  // 2th pin
	EXTI->RTSR1 |= (1U << 8);  // 8th pin

	/* Mask */
	EXTI->IMR1 |= (1U << 9);
	EXTI->IMR1 |= (1U << 0);
	EXTI->IMR1 |= (1U << 2);
	EXTI->IMR1 |= (1U << 8);

	/* NVIC */
	NVIC_SetPriority(EXTI0_1_IRQn , 1);
	NVIC_EnableIRQ(EXTI0_1_IRQn);

	NVIC_SetPriority(EXTI2_3_IRQn , 0);
	NVIC_EnableIRQ(EXTI2_3_IRQn);

	NVIC_SetPriority(EXTI4_15_IRQn , 2);
	NVIC_EnableIRQ(EXTI4_15_IRQn);

	/* Setup PA0, PA1, PA4, PA5, PA12, PA11, PB3 as output for SSD */
	GPIOA->MODER &= ~(3U << 2*0);
	GPIOA->MODER |=  (1U << 2*0);  // PA0 is output
	GPIOA->MODER &= ~(3U << 2*1);
	GPIOA->MODER |=  (1U << 2*1);  // PA1 is output
    GPIOA->MODER &= ~(3U << 2*4);
	GPIOA->MODER |=  (1U << 2*4);  // PA4 is output
	GPIOA->MODER &= ~(3U << 2*5);
	GPIOA->MODER |=  (1U << 2*5);  // PA5 is output
	GPIOA->MODER &= ~(3U << 2*12);
	GPIOA->MODER |=  (1U << 2*12);  // PA12 is output
	GPIOA->MODER &= ~(3U << 2*11);
	GPIOA->MODER |=  (1U << 2*11);  // PA11 is output
	GPIOB->MODER &= ~(3U << 2*3);
	GPIOB->MODER |=  (1U << 2*3);  // PB3 is output
	GPIOA->MODER &= ~(3U << 2*7);
	GPIOA->MODER |=  (1U << 2*7);  // PA7 is output (dot)

	/* Set all rows */
	GPIOA->ODR |= (1U << 8);
	GPIOA->ODR |= (1U << 9);
	GPIOA->ODR |= (1U << 5);
	GPIOA->ODR |= (1U << 4);

SystemCoreClockUpdate();
InitTimer();
InitTimer2();
SpeakerInit();
	clearSSD();
	while(1) {
display();
	}

	return 0;
}

void clearSSD(void){
	/* Set all outputs connected to SSD (clear SSD) */
	GPIOA->ODR |= (1U << 0);   // PA0  A
	GPIOA->ODR |= (1U << 1);   // PA1  B
	GPIOA->ODR |= (1U << 4);   // PA4  C
	GPIOA->ODR |= (1U << 5);   // PA5  D
	GPIOA->ODR |= (1U << 12);  // PA12 E
	GPIOA->ODR |= (1U << 11);  // PA11 F
	GPIOB->ODR |= (1U << 3);   // PB3  G
	GPIOA->ODR |= (1U << 7);   // PA7  *
}
void setSSD( int x ) {
	clearSSD();
	switch ( x )
	{
	case 0:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		GPIOA->ODR &= ~(1U << 5);   // PA5  D
		GPIOA->ODR &= ~(1U << 12);  // PA12 E
		GPIOA->ODR &= ~(1U << 11);  // PA11 F
		break;
	case 1:
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		break;
	case 2:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 5);   // PA5  D
		GPIOA->ODR &= ~(1U << 12);  // PA12 E
		GPIOB->ODR &= ~(1U << 3);   // PB3  G
		break;
	case 3:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		GPIOA->ODR &= ~(1U << 5);   // PA5  D
		GPIOB->ODR &= ~(1U << 3);   // PB3  G
		break;
	case 4:
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		GPIOA->ODR &= ~(1U << 11);  // PA11 F
		GPIOB->ODR &= ~(1U << 3);   // PB3  G
		break;
	case 5:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		GPIOA->ODR &= ~(1U << 5);   // PA5  D
		GPIOA->ODR &= ~(1U << 11);  // PA11 F
		GPIOB->ODR &= ~(1U << 3);   // PB3  G
		break;
	case 6:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		GPIOA->ODR &= ~(1U << 5);   // PA5  D
		GPIOA->ODR &= ~(1U << 12);  // PA12 E
		GPIOA->ODR &= ~(1U << 11);  // PA11 F
		GPIOB->ODR &= ~(1U << 3);   // PB3  G
		break;
	case 7:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		break;
	case 8:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		GPIOA->ODR &= ~(1U << 5);   // PA5  D
		GPIOA->ODR &= ~(1U << 12);  // PA12 E
		GPIOA->ODR &= ~(1U << 11);  // PA11 F
		GPIOB->ODR &= ~(1U << 3);   // PB3  G
		break;
	case 9:
		GPIOA->ODR &= ~(1U << 0);   // PA0  A
		GPIOA->ODR &= ~(1U << 1);   // PA1  B
		GPIOA->ODR &= ~(1U << 4);   // PA4  C
		GPIOA->ODR &= ~(1U << 5);   // PA5  D
		GPIOA->ODR &= ~(1U << 11);  // PA11 F
		GPIOB->ODR &= ~(1U << 3);   // PB3  G
		break;

		case 10: // A
GPIOA->ODR &= ~(1U << 0); // A
GPIOA->ODR &= ~(1U << 1); // B
GPIOA->ODR &= ~(1U << 4); // C
GPIOA->ODR &= ~(1U << 12); // E
GPIOA->ODR &= ~(1U << 11); // F
GPIOB->ODR &= ~(1U << 3);  //  G
break;
case 11: // S
GPIOA->ODR &= ~(1U << 0); // A
GPIOA->ODR &= ~(1U << 4); // C
GPIOA->ODR &= ~(1U << 5); // D
GPIOA->ODR &= ~(1U << 11); // F
GPIOB->ODR &= ~(1U << 3);  //  G
break;
case 12: // t
GPIOA->ODR &= ~(1U << 5); // D
GPIOA->ODR &= ~(1U << 12); // E
GPIOA->ODR &= ~(1U << 11); // F
GPIOB->ODR &= ~(1U << 3);  //  G
break;
case 13: // n
GPIOA->ODR &= ~(1U << 4); // C
GPIOA->ODR &= ~(1U << 12); // E
GPIOB->ODR &= ~(1U << 3);  //  G
break;
case 14: // E
GPIOA->ODR &= ~(1U << 0); // A
GPIOA->ODR &= ~(1U << 5); // D
GPIOA->ODR &= ~(1U << 12); // E
GPIOA->ODR &= ~(1U << 11); // F
GPIOB->ODR &= ~(1U << 3);  //  G
break;
case 15: // q
GPIOA->ODR &= ~(1U << 0); // A
GPIOA->ODR &= ~(1U << 1); // B
GPIOA->ODR &= ~(1U << 4); // C
GPIOA->ODR &= ~(1U << 11); // F
GPIOB->ODR &= ~(1U << 3);  //  G
break;
case 16: // r
GPIOA->ODR &= ~(1U << 12); // E
GPIOB->ODR &= ~(1U << 3);  //  G
break;
	}
}
void clearRowsKeypad(void){
	/* Clearing the rows here */
	GPIOA->ODR &= ~(1U << 8);  // PA8
	GPIOB->ODR &= ~(1U << 9);  // PB9
	GPIOB->ODR &= ~(1U << 5);  // PB5
	GPIOB->ODR &= ~(1U << 4);  // PB4
}
void setRowsKeypad(void){
	/* Setting the rows here */
	GPIOA->ODR |= (1U << 8);  // PA8
	GPIOB->ODR |= (1U << 9);  // PB9
	GPIOB->ODR |= (1U << 5);  // PB5
	GPIOB->ODR |= (1U << 4);  // PB4
}

void on_SSD1() {/* turn on SSD 1(LEFT).*/
	 /* turn on ODR*/
	GPIOB->ODR |= (0x40);
}
void off_SSD1() {/* turn off SSD 1(LEFT).*/
	 /* turn on ODR*/
	GPIOB->BRR |= (0x40);
}
void on_SSD2() {/* turn on SSD 2.*/
	 /* turn on ODR*/
	GPIOB->ODR |= (0x80);
}
void off_SSD2() {/* turn off SSD 2.*/
	 /* turn on ODR*/
	GPIOB->BRR |= (0x80);
}
void on_SSD3() {/* turn on SSD 3.*/
	 /* turn on ODR*/
	GPIOB->ODR |= (0x2);
}
void off_SSD3() {/* turn off SSD 3.*/
	 /* turn on ODR*/
	GPIOB->BRR |= (0x2);
}
void on_SSD4() {/* turn on SSD 4.*/
	 /* turn on ODR*/
	GPIOA->ODR |= (0x400);
}
void off_SSD4() {/* turn off SSD 4.*/
	 /* turn on ODR*/
	GPIOA->BRR |= (0x400);
}
void display(){
	clearSSD();
	    on_SSD1();
		setSSD(l); // en sol
		delay(3000);
		off_SSD1();
		delay(100);

		on_SSD2();
		setSSD(k);
		delay(3000);
		off_SSD2();
		delay(100);

		on_SSD3();
		setSSD(j);
		delay(3000);
		off_SSD3();
		delay(100);

		on_SSD4();
		setSSD(i); // en sağ
		delay(3000);
		off_SSD4();
		delay(100);

}
void delay(volatile uint32_t s) {
    for(; s>0; s--);
}
void shift(int x){
	clearSSD();
switch (x){
    i=0;
    j=0;
    case 0:
    k=0;
    l=5;
    tone=5000;
    break;
    case 1:
    k=0;
    l=3;
    tone=3000;
    break;
    case 2:
    k=0;
    l=9;
    tone=9000;
    break;
    case 3:
    k=0;
    l=7;
    tone=7000;
    break;
    case 4:
    k=2;
    l=5;
    tone=5200;
    break;
    case 5:
    k=0;
    l=4;
    tone=4000;
    break;
    case 6:
    tone=5400;
    k=4;
    l=5;
    break;
    case 7:
    tone=6400;
    k=4;
    l=6;
    break;
    case 8:
    k=0;
    l=0;
    tone=0;
    break;
    case 9:
    k=8;
    l=4;
    tone=4800;
    break;
    case 10:
    k=0;
    l=6;
    tone=6000;
    break;
    case 11:
    k=2;
    l=7;
    tone=7200;
    break;
    case 12:
    k=4;
    l=4;
    tone=4400;
    break;
    case 13:
    k=6;
    l=5;
    tone=5600;
    break;
    case 14:
    k=8;
    l=6;
    tone=6800;
    break;
    case 15:
    k=6;
    l=6;
    tone=6600;
    break;
}

}


void InitTimer(){
RCC->APBENR1 |=(1U<<1);
TIM3->CR1=0;
TIM3->CR1 |=(1<<7);
TIM3->CNT =0;
TIM3->PSC=0;
TIM3->ARR=(1600000);
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
TIM2->ARR=(8000000);
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
