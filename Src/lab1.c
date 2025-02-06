#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>

int lab1_main(void){
    HAL_Init();
    SystemClock_Config();

    My_HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef initStr = {GPIO_PIN_7 | GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};

    GPIO_InitTypeDef initButton = {GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_SPEED_FREQ_LOW, GPIO_PULLDOWN};

    My_HAL_GPIO_Init(GPIOA, &initButton);

    My_HAL_GPIO_Init(GPIOC, &initStr);
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    while (1) {
        HAL_Delay(200);
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7 | GPIO_PIN_6);
    }      
}