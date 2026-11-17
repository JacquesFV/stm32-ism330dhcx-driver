#ifndef GPIO_EXTI_H_
#define GPIO_EXTI_H_

#include <stdint.h>
#include "stm32f4xx.h"

#define LINE13	(1U<<13)
void pc13_exti_init(void);

#endif
