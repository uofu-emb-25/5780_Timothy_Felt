#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>

int lab1_main(void){
    HAL_Init();
    SystemClock_Config();

    My_HAL_RCC_GPIOC_CLK_ENABLE();
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIO_InitTypeDef initStr = {GPIO_PIN_7 | GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};

    GPIO_InitTypeDef initButton = {GPIO_PIN_0, GPIO_MODE_INPUT, GPIO_SPEED_FREQ_LOW, GPIO_PULLDOWN};

    My_HAL_GPIO_Init(GPIOA, &initButton);

    My_HAL_GPIO_Init(GPIOC, &initStr);
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    /*while (1) {
        HAL_Delay(200);
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7 | GPIO_PIN_6);
    } */
    uint32_t debouncer = 0;
    while(1) {
    debouncer = (debouncer << 1); // Always shift every loop iteration
    if (My_HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)) { // If input signal is set/high
    debouncer |= 0x01; // Set lowest bit of bit-vector
    }
    if (debouncer == 0xFFFFFFFF) {
    // This code triggers repeatedly when button is steady high!
    }
    if (debouncer == 0x00000000) {
    // This code triggers repeatedly when button is steady low!
    }
    if (debouncer == 0x7FFFFFFF) {
        My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);
    // This code triggers only once when transitioning to steady high!
    }
    // When button is bouncing the bit-vector value is random since bits are set when the button is high and not when it bounces low.
    }
}