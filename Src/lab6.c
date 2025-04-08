#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>
#include <stdio.h>

int lab6_main(void){
    HAL_Init();
    SystemClock_Config();
    My_HAL_RCC_GPIOC_CLK_ENABLE();
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIO_InitTypeDef initStr = {GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    My_HAL_GPIO_Init(GPIOC, &initStr);
    SetUpADC();
    while(1){
        if(ADC1->DR > 0){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);

        }
        if(ADC1->DR > 64){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);

        }
        if(ADC1->DR > 128){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);


        }
        if(ADC1->DR > 192){
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);

        }
        HAL_Delay(100);
    }
    // SetUpDAC();
    // const uint8_t sine_table[32] = {127,151,175,197,216,232,244,251,254,251,244,
    // 232,216,197,175,151,127,102,78,56,37,21,9,2,0,2,9,21,37,56,78,102};
    // while(1){
    //     for(int i = 0; i < 32; i++){
    //         DAC->DHR8R2 = sine_table[i];
    //         HAL_Delay(1);
    //     }
    // }


}