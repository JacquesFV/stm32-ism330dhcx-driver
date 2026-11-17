#include "embedded.h"

int main(void)
{
	//enable clock access to GPIOA
	RCC_AHB1EN_R |= GPIOAEN;

	//set bit 10 to 1
	GPIOA_MODE_R |= (1U<<10);
	//set bit 11 to 0
	GPIOA_MODE_R &= ~(1U<<11);

	while(1){
		//set PA5 (LED_PIN) high
		GPIOA_OD_R ^= LED_PIN;
		for(int i = 0; i < 100000;i++){} //delay loop for visible blinking
	}

}
