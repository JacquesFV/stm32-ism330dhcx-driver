#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "my_ism330dhcx.h"





int main(void)
{
	/*Initialize debug UART*/
	uart_init();

	/*Initialize ism330*/
	my_ism330_init();


	int16_t ax, ay,  az;
	while(1)
	{
      my_ism330_get_accel(&ax,&ay,&az);
      printf("AX=%d AY=%d AZ=%d\r\n",
                 ax, ay, az);
      
      
     

	  for(volatile int i = 0; i < 1000000; i++);



	}
}
