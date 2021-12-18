
#include "stm32g0xx.h"
enum states{s0,s1,s2,s3,s4,s5}mode;
int s=0;
int count=0;
int main(void) {

    /* Enable GPIOB clock */
    RCC->IOPENR |= (1U << 1);

    /* Setup PB2 as output */
    GPIOB->MODER &= ~(3U << 4);
    GPIOB->MODER |= (1U << 4);
    /* Setup PB4 as input */
    GPIOB->MODER &= ~(3U << 8);

    while(1){
    	if((GPIOB->IDR >> 4) & 1){
    		if(count==0){
    			mode=s0;
    		}else if(count==1){
    			mode=s1;
    		}else if(count==2){
    			mode=s2;
    		}else if(count==3){
    			mode=s3;
    		}else if(count==4){
    			mode=s4;
    		}else if(count==5){
    			mode=s5;
    		}else{
    			count=0;
    		}
    		count++;
    	}


    if (mode==s0){
    	 /*Turn off LED */
    	    GPIOB->BRR |= (1U << 2);
    }else if(mode==s1){
        /* Turn on LED */
        GPIOB->ODR |= (1U << 2);
        /* delay*/
        for(s=2000000; s>0; s--);
        /*Turn off LED */
        GPIOB->BRR |= (1U << 2);
        for(s=2000000; s>0; s--);
}else if(mode==s2){
    /* Turn on LED */
    GPIOB->ODR |= (1U << 2);
    /* delay*/
    for(s=1000000; s>0; s--);
    /*Turn off LED */
    GPIOB->BRR |= (1U << 2);
    for(s=1000000; s>0; s--);
}else if(mode==s3){
    /* Turn on LED */
    GPIOB->ODR |= (1U << 2);
    /* delay*/
    for(s=500000; s>0; s--);
    /*Turn off LED */
    GPIOB->BRR |= (1U << 2);
    for(s=500000; s>0; s--);
}else if(mode==s4){
    /* Turn on LED */
    GPIOB->ODR |= (1U << 2);
    /* delay*/
    for(s=100000; s>0; s--);
    /*Turn off LED */
    GPIOB->BRR |= (1U << 2);
    for(s=100000; s>0; s--);
}else if(mode==s5){
    /* Turn on LED */
    GPIOB->ODR |= (1U << 2);
    /* delay*/
}
}
    return 0;
}
