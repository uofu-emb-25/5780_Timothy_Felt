#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    if (GPIOx == GPIOA)
    {
        GPIOx->MODER &=~(GPIO_MODER_MODER0);
        GPIOx->OSPEEDR &=~(GPIO_OSPEEDR_OSPEEDR0);
        GPIOx->PUPDR |=(GPIO_PUPDR_PUPDR0_1);
    }
    if (GPIOx == GPIOC)
    {
        GPIOx->MODER |=(GPIO_MODER_MODER7_0 | GPIO_MODER_MODER6_0|GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
        // Register OTYPER is in the correct state.
        //Register Ospeedr is already in the correct state.
        // PUPDR Is already in the correct state.
    }

}

void My_HAL_RCC_GPIOC_CLK_ENABLE(){
    RCC->AHBENR |=(RCC_AHBENR_GPIOCEN);
}

void EXTI_INTERRUPT(){
    EXTI->IMR |= (EXTI_IMR_IM0);
    EXTI->RTSR |= (EXTI_RTSR_RT0);
    NVIC_EnableIRQ(EXTI0_1_IRQn);

}

void EXTI0_1_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0){
        EXTI->PR = EXTI_PR_PR0;

    }
    My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
    My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
    volatile int wait = 1500000;
    while (wait > 0){
        wait--;
    }

    }

void SYSCONFIG_ROUTE_PA0_EXTI0(){
    RCC->APB2ENR |= (RCC_APB2ENR_SYSCFGCOMPEN);
    //routing to from EXTI0 to PA0 doesnt need to be programmed as they are assigned to each other by default.


}
void TIM2_IRQHandler() {
    
}
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
}



GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint16_t ReadBit = GPIOx->IDR & GPIO_Pin;
    if (ReadBit == 0){
        return 0;
    }
    else {
        return 1;
    }
}



void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if(PinState == GPIO_PIN_SET){
        GPIOx->BSRR = GPIO_Pin;
    }
    else {
        GPIOx->BRR = GPIO_Pin;
    }
}



void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    uint16_t temp = GPIOx->ODR;
    GPIOx->BRR = GPIO_Pin;
    GPIOx->BSRR = temp ^ GPIO_Pin;


}

void My_HAL_TIMED_TogglePin(){
    RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN);
    TIM2->PSC = 0x1F3F;
    TIM2->ARR = 0x000000FA;
    TIM2->DIER |= (TIM_DIER_UIE);
    TIM2->CR1 |= (TIM_CR1_CEN);
}


