#include "main.h"
#include <stm32f0xx_hal.h>
#include <hal_gpio.h>
#include <stdio.h>

int lab5_main(void){
    //initialize I2C GPIO pins
    RCC->AHBENR |=(RCC_AHBENR_GPIOBEN);
    RCC->AHBENR |=(RCC_AHBENR_GPIOCEN);
    RCC->APB1ENR |=(RCC_APB1ENR_I2C2EN);

    //Initialize pin B11 and set it up
    GPIOB->MODER &= ~(0x3 << (11*2));
    GPIOB->MODER |= (0x2 << (11*2));
    GPIOB->OTYPER |= GPIO_OTYPER_OT_11;
    GPIOB->AFR[1] &= ~(0xF << (3*4));
    GPIOB->AFR[1] |= (0x1 << (3*4));

    //Initialize pin B13 and set it up
    GPIOB->MODER &= ~(0x3 << (13*2));
    GPIOB->MODER |= (0x2 << (13*2));
    GPIOB->OTYPER |= GPIO_OTYPER_OT_13;
    GPIOB->AFR[1] &= ~(0xF << (5*4));
    GPIOB->AFR[1] |= (0x5 << (5*4));

    //Initialize pin B14 and set it up
    GPIOB->MODER &= ~(0x3 << (14*2));
    GPIOB->MODER |= (0x1 << (14*2));
    My_HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);

    //Initialize and Set PC0
    GPIOC->MODER &= ~(0x3);
    GPIOC->MODER |= (0x1);
    My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);

    //Initialize and set up orange, red, and green leds.
    GPIO_InitTypeDef initStr = {GPIO_PIN_8 | GPIO_PIN_6 | GPIO_PIN_9 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    My_HAL_GPIO_Init(GPIOC, &initStr);





    //enable and setup 12C2 peripheral.
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    I2C2->TIMINGR = 0x0;
    I2C2->TIMINGR |= 0x1 << 28;
    I2C2->TIMINGR |= 0x4 << 20;
    I2C2->TIMINGR |= 0x2 << 16;
    I2C2->TIMINGR |= 0x13;
    I2C2->TIMINGR |= 0xF << 8;
    I2C2->CR1 |= I2C_CR1_PE;

    //setup Transaction 
    SetUpI2C(0,1);

    while(1)
    {
        while(!(I2C2->ISR & I2C_ISR_NACKF || I2C2->ISR & I2C_ISR_TXIS)){
        }

        if(I2C2->ISR & I2C_ISR_NACKF){
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
            break;
        }
        if(I2C2->ISR & I2C_ISR_TXIS){
            I2C2->TXDR = 0x0F;
        }
        while(!(I2C2->ISR & I2C_ISR_TC))
        {
        }
        SetUpI2C(1,1);

        while(!(I2C2->ISR & (I2C_ISR_RXNE | I2C_ISR_NACKF)))
        {
        }
        int myReg = I2C2->RXDR;
        while(!(I2C2->ISR & I2C_ISR_TC))
        {}
        if(myReg == 0xD3){
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
        }
        else{
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
        }

        I2C2->CR2 |= (1 << I2C_CR2_STOP_Pos);
        EnableXandYGyro();

    }
}
