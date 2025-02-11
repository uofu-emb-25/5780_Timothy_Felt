#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>
#include <stm32f0xx_it.h>

int lab2_main(void){
    HAL_Init;
    SystemClock_Config();

    My_HAL_RCC_GPIOC_CLK_ENABLE();
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIO_InitTypeDef initStr = {GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};

    My_HAL_GPIO_Init(GPIOC, &initStr);
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);

    GPIOA->PUPDR |=(GPIO_PUPDR_PUPDR0_1);
    //PA0 by default is already in low-speed and in input mode. So no code is needed.
    EXTI_INTERRUPT();
    while (1) {
        HAL_Delay(400);
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    } 
}


