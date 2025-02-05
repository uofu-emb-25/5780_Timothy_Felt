#include "main.h"
#include <stm32f0xx_hal.h>

int lab1_main(void){
    HAL_Init();
    SystemClock_Config();

    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef initStr = {GPIO_PIN_7 | GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};

    HAL_GPIO_Init(GPIOC, &initStr);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    while (1) {
        HAL_Delay(200);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7 | GPIO_PIN_6);
    }      
}