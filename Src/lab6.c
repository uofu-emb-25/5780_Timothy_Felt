#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>
#include <stdio.h>

int lab6_main(void){
    HAL_Init();
    SystemClock_Config();
    GPIO_InitTypeDef initStr = {GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    My_HAL_GPIO_Init(GPIOC, &initStr);
    

}