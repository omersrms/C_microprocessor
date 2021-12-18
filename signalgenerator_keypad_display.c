
#include "stm32g0xx.h"

void clearSSD		( void );
void setSSD			( int );

void clearRowsKeypad( void );
void setRowsKeypad  ( void );
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
// diez geldiginde ne yapsin ????
SAVE();
delay(100000);
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

// ********************************************************
active=1;
count1=1;
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
//CYCLE DISPLAY
count2++;
cycledisplay();
delay(500000); // cift okumamali
}
GPIOA->ODR ^= (1U << 8); //PA8
GPIOB->ODR ^= (1U << 9); //PB9
if ((GPIOA->IDR >> 9) & 1 ) { // read PA9
// CYCLE MODES
cyclemodes();
delay(500000);
}
GPIOB->ODR ^= (1U << 9); //PB9
GPIOB->ODR ^= (1U << 5); //PB5
if ((GPIOA->IDR >> 9) & 1 ) { // read PA9
//FREQUENCY MODE
F_SAVE=1;
delay(100000);
}
GPIOB->ODR ^= (1U << 5); //PB5
GPIOB->ODR ^= (1U << 4); //PB4
if ((GPIOA->IDR >> 9) & 1 ) { // read PA9
// AMPLITUDE MODE
A_SAVE=1;
delay(100000);
}
GPIOB->ODR ^= (1U << 4); //PB4
EXTI->RPR1 |= (1U << 9);
setRowsKeypad();
}
}

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
const uint32_t tri_table[128] = {
0, 16, 32, 48, 64, 81, 97, 113, 129, 145, 161, 177, 193, 209, 226,
242, 258, 274, 290, 306, 322, 338, 354, 371, 387, 403, 419, 435, 451, 467,
483, 499, 516, 532, 548, 564, 580, 596, 612, 628, 644, 661, 677, 693, 709,
725, 741, 757, 773, 789, 806, 822, 838, 854, 870, 886, 902, 918, 934, 951,
967, 983, 999, 1015, 1015, 999, 983, 967, 951, 934, 918, 902, 886, 870, 854,
838, 822, 806, 789, 773, 757, 741, 725, 709, 693, 677, 661, 644, 628, 612,
596, 580, 564, 548, 532, 516, 499, 483, 467, 451, 435, 419, 403, 387, 371,
354, 338, 322, 306, 290, 274, 258, 242, 226, 209, 193, 177, 161, 145, 129,
113, 97, 81, 64, 48, 32, 16, 0
};
const uint32_t saw_table[128] = {
0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 81, 89, 97, 105, 113,
121, 129, 137, 145, 153, 161, 169, 177, 185, 193, 201, 209, 217, 226, 234,
242, 250, 258, 266, 274, 282, 290, 298, 306, 314, 322, 330, 338, 346, 354,
362, 371, 379, 387, 395, 403, 411, 419, 427, 435, 443, 451, 459, 467, 475,
483, 491, 499, 507, 516, 524, 532, 540, 548, 556, 564, 572, 580, 588, 596,
604, 612, 620, 628, 636, 644, 652, 661, 669, 677, 685, 693, 701, 709, 717,
725, 733, 741, 749, 757, 765, 773, 781, 789, 797, 806, 814, 822, 830, 838,
846, 854, 862, 870, 878, 886, 894, 902, 910, 918, 926, 934, 942, 951, 959,
967, 975, 983, 991, 999, 1007, 1015, 0
};
const uint32_t sqrt_table[128] = {
1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
1023, 1023, 1023, 1023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 1023
};
const uint32_t whtnoise_table[128] = {
893, 88, 805, 656, 1094, 294, 837, 917, 52, 591, 1328, 569, 354, 745, 371,
738, 443, 502, 747, 1208, 743, 1355, -526, 282, 632, 84, -141, 827, 825, 660,
714, 66, 257, 457, 160, 681, 1721, 265, 843, -18, 1197, 16, 618, 195, 773,
517, 489, 2020, 189, 488, 1884, -75, 794, -39, 1039, 679, 845, 369, 637, 1265,
-652, -324, 724, 177, 360, -254, 49, 305, 140, 68, 296, 29, 1198, 6, 1441,
320, -231, 195, 989, 1052, 593, 659, 835, -235, 214, -425, 282, 997, 878, 1682,
597, -592, 1376, 1167, 213, 625, 910, 708, 868, 454, 492, 557, 108, 1239, 515,
863, 74, -38, 465, 382, 1123, 822, 788, -228, 17, 615, 334, 1171, 1198, 214,
959, 1225, 676, 1342, 1055, 621, 960, 611
};
const uint32_t rnddigit_table[128] = {
512, 1023, 512, 512, 512, 512, 1023, 1023, 512, 512, 1023, 1023, 512, 512, 512,
1023, 1023, 512, 1023, 512, 512, 1023, 1023, 1023, 1023, 512, 1023, 512, 1023, 1023,
1023, 1023, 1023, 512, 512, 512, 1023, 512, 1023, 1023, 1023, 512, 512, 1023, 512,
512, 1023, 512, 1023, 512, 512, 512, 512, 1023, 512, 1023, 512, 512, 512, 512,
1023, 512, 1023, 1023, 1023, 512, 1023, 512, 512, 512, 512, 1023, 512, 512, 512,
512, 1023, 512, 512, 512, 1023, 1023, 1023, 1023, 1023, 512, 512, 512, 1023, 1023,
1023, 512, 1023, 512, 512, 1023, 512, 512, 512, 1023, 512, 512, 512, 1023, 1023,
512, 1023, 512, 1023, 512, 512, 1023, 512, 512, 512, 1023, 512, 512, 1023, 512,
1023, 512, 1023, 512, 512, 1023, 1023, 1023
};

void TIM3_IRQHandler(void){
TIM3->SR &= ~(1U<<0);
TIM3->SR &= ~(1U<<1);
}

void TIM2_IRQHandler(void) {
    // update duty (CCR2)
if(mode==1){
TIM3->ARR=a_tim*(sin_table[counter_t]);
	counter_t++;
	if(counter_t>128){
		counter_t = 0;
	}
}else if(mode==2){
   TIM3->ARR=a_tim*(sqrt_table[counter_t]);
	counter_t++;
	if(counter_t>128){
		counter_t = 0;
	}
}else if(mode==3){
   TIM3->ARR=a_tim*(tri_table[counter_t]);
	counter_t++;
	if(counter_t>128){
		counter_t = 0;
	}
}else if(mode==4){
   TIM3->ARR=a_tim*(saw_table[counter_t]);
	counter_t++;
	if(counter_t>128){
		counter_t = 0;
	}
}else if(mode==5){
   TIM3->ARR=a_tim*(whtnoise_table[counter_t]);
	counter_t++;
	if(counter_t>128){
		counter_t = 0;
	}
}else if(mode==6){
   TIM3->ARR=a_tim*(rnddigit_table[counter_t]);
	counter_t++;
	if(counter_t>128){
		counter_t = 0;
	}
}

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
case 17: //*
GPIOA->ODR &= ~(1U << 7);  //  G
break;
case 18: // U
GPIOA->ODR &= ~(1U << 1); // B
GPIOA->ODR &= ~(1U << 4); // C
GPIOA->ODR &= ~(1U << 5); // D
GPIOA->ODR &= ~(1U << 12); // E
GPIOA->ODR &= ~(1U << 11); // F
break;
case 19: // h
GPIOA->ODR &= ~(1U << 4); // C
GPIOA->ODR &= ~(1U << 12); // E
GPIOA->ODR &= ~(1U << 11); // F
GPIOB->ODR &= ~(1U << 3);  //  G
break;
case 20: // d
GPIOA->ODR &= ~(1U << 1); // B
GPIOA->ODR &= ~(1U << 4); // C
GPIOA->ODR &= ~(1U << 5); // D
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
	dot();
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
    temp1=i;
    temp2=j;
    temp3=k;
    j=temp1;
    k=temp2;
    l=temp3;
    i=x;
    count1++;
    if(count1>4){
    	count1=0;
    	active=0;
    }
}
void dot(){
	clearSSD();
	if(active==1){
	if(count1==1){
    on_SSD4();
	setSSD(17);
	delay(3000);
	off_SSD4();
	delay(100);
	}else if(count1==2){
	    on_SSD3();
		setSSD(17);
		delay(3000);
		off_SSD3();
		delay(100);
	}else if(count1==3){
	    on_SSD2();
		setSSD(17);
		delay(3000);
		off_SSD2();
		delay(100);
	}else if(count1==4){
	    on_SSD1();
		setSSD(17);
		delay(3000);
		off_SSD1();
		delay(100);
	}else if(count1==0){
		clearSSD();
	}
	}
}

void SAVE(){
clearSSD();
	delay(100000);
    if(A_SAVE==1){
		if(count1==0 || count1==1){
		amplitude=(l*1000)+(k*100)+(j*10)+i;
		}else if(count1==2){
		amplitude=(l*100)+(k*10)+(j*1)+(i*(0.1));
		}else if(count1==3){
		amplitude=(l*10)+(k*1)+(j*(0.1))+(i*(0.01));
		}else if(count1==4){
		amplitude=(l*1)+(k*(0.1))+(j*(0.01))+(i*(0.001));
		}
		if(amplitude <= 3.3){
			a_tim=(1023/3.3)*amplitude;
		}
		a1=l;
		a2=k;
		a3=j;
		a4=i;
		dotpos1=count1;
		A_SAVE=0;
	}
	delay(100000);
	if(F_SAVE==1){
		if(count1==0 || count1==1){
		frequency=(l*1000)+(k*100)+(j*10)+i;
		}else if(count1==2){
		frequency=(l*100)+(k*10)+(j*1)+(i*(0.1));
		}else if(count1==3){
		frequency=(l*10)+(k*1)+(j*(0.1))+(i*(0.01));
		}else if(count1==4){
		frequency=(l*1)+(k*(0.1))+(j*(0.01))+(i*(0.001));
		}
		f_tim=128000/frequency;
		f1=l;
		f2=k;
		f3=j;
		f4=i;
		dotpos2=count1;
		F_SAVE=0;
	}
	delay(100000);
}

void cycledisplay(){
	clearSSD();
if(count2==1){ // mode
modename(mode); // current mode value
}else if(count2==2){ // Amplitude
delay(50000);
l=a1;
k=a2;
j=a3;
i=a4;
count1=dotpos1;
delay(100000);
}else if(count2==3){ // Frequency
delay(50000);
l=f1;
k=f2;
j=f3;
i=f4;
count1=dotpos2;
delay(100000);
count2=0;
}
}

void cyclemodes(){
    count3++;
	if(count3>6){
		count3=1;
	}
    switch ( count3 ){
	case 1://sine
mode=1;
		break;
	case 2://square
mode=2;
		break;
	case 3://triangle
mode=3;
		break;
	case 4://sawtooth
mode=4;
		break;
	case 5://white noise
mode=5;
		break;
	case 6://random digital
mode=6;
		break;
	}
	modename(mode);
}

void modename(int a){
	clearSSD();
	count1=0;
	switch ( a )
	{
	case 1://sine
l=11;
k=1;
j=13;
i=14;
		break;
	case 2://square
l=11;
k=15;
j=16;
i=12;
		break;
	case 3://triangle
l=12;
k=16;
j=1;
i=10;
		break;
	case 4://sawtooth
l=11;
k=10;
j=18;
i=18;
		break;
	case 5://white noise
l=18;
k=18;
j=19;
i=12;
		break;
	case 6://random digital
l=16;
k=10;
j=13;
i=20;
		break;
}
}

void InitTimer(){
RCC->APBENR1 |=(1U<<1);
TIM3->CR1=0;
TIM3->CR1 |=(1<<7);
TIM3->CNT =0;
TIM3->PSC=0;
TIM3->ARR=(1600);
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
TIM2->ARR=(f_tim);
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
