#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>

int lab4_main(void){
    HAL_Init();
    SystemClock_Config();
    My_HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef initStr = {GPIO_PIN_10 | GPIO_PIN_11, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    My_HAL_GPIO_Init(GPIOC, &initStr);


    __NVIC_EnableIRQ(USART3_4_IRQn);
    __NVIC_SetPriority(USART3_4_IRQn, 2);

    CREATE_TRANSMIT_RECEIVE();


    while(1){
        Keystroke_Led_Toggle();
    }
}
