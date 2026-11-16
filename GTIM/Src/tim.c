#include "tim.h"

#define TIM2EN		(1U<<0)
#define CR1_CEN		(1U<<0)

void tim2_1hz_init(void){
	/*UEV = Timer Clock/((Prescaler + 1) * (Period + 1))*/
	/*UEV = 16000000/((1599+1)*(9999+1)) = 1Hz */
	/*Enable clock access to tim2*/
	RCC->APB1ENR |=TIM2EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600 -1;
	/*Set auto-reload value*/
	TIM2->ARR = 10000 -1;
	/*Clear counter*/
	TIM2->CNT = 0;

	/*Enable timer*/
	TIM2->CR1 = CR1_CEN;
}
