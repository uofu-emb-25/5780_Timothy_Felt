#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>
#include <stm32f0xx_it.h>
#include <assert.h>
#include <stdio.h>

int lab2_main(void){
    HAL_Init();
    SystemClock_Config();

    My_HAL_RCC_GPIOC_CLK_ENABLE();
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIO_InitTypeDef initStr = {GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    GPIO_InitTypeDef initButton = {GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_SPEED_FREQ_LOW, GPIO_PULLDOWN};

    My_HAL_GPIO_Init(GPIOA, &initButton);


    My_HAL_GPIO_Init(GPIOC, &initStr);
    My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);


    GPIOA->PUPDR |=(GPIO_PUPDR_PUPDR0_1);
    //PA0 by default is already in low-speed and in input mode. So no code is needed.
    assert(EXTI->IMR == 0x7F840000);
    assert(EXTI->RTSR == 0x00000000);
    EXTI_INTERRUPT();
    assert(EXTI->IMR == 0x7F840001);
    assert(EXTI->RTSR == 0x00000001);
    assert(SYSCFG->EXTICR[1] == 0x0000);
    SYSCONFIG_ROUTE_PA0_EXTI0();
    assert(SYSCFG->EXTICR[1] == 0x0000);
    __NVIC_EnableIRQ(EXTI0_1_IRQn);
    __NVIC_SetPriority(EXTI0_1_IRQn, 1);
    while (1) {
        HAL_Delay(400);
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
    } 
}


