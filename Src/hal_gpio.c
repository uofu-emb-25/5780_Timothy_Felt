#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>
#include <stdio.h>

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
    My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
    My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
    TIM2->SR &=~(TIM_SR_UIF);
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

void My_HAL_DIM_LED_TIM3(){
    RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN);
    TIM3->PSC = 0x0028;
    TIM3->ARR = 0x000000FA;
    //no need to set CC1s or CC2s as they are configured to output by default.
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_0;
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_2;
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_0;
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_1;
    TIM3->CCMR1 |= TIM_CCMR1_OC2M_2;
    TIM3->CCMR1 |= TIM_CCMR1_OC2PE;
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM3->CCER |= TIM_CCER_CC1E;
    TIM3->CCER |= TIM_CCER_CC2E;
    TIM3->CCR1 = 5;
    TIM3->CCR2 = 50;
    GPIOC->MODER &= ~(0x3 << 2*7);
    GPIOC->MODER &= ~(0x3 << 2*6);
    GPIOC->MODER |= GPIO_MODER_MODER7_1;
    GPIOC->MODER |= GPIO_MODER_MODER6_1;
    GPIOC->AFR[0] &= ~(0x15 << 4*6);
    GPIOC->AFR[0] &= ~(0x15 << 4*7);
    TIM3->CR1 |= (TIM_CR1_CEN);

}

void CREATE_TRANSMIT_RECEIVE(){
    GPIOC->MODER |= GPIO_MODER_MODER10_1;
    GPIOC->MODER |= GPIO_MODER_MODER11_1;
    GPIOC->AFR[1] &= ~GPIO_AFRH_AFSEL10_Msk;
    GPIOC->AFR[1] &= ~GPIO_AFRH_AFSEL11_Msk;
    GPIOC->AFR[1] |= GPIO_AF1_USART3<<GPIO_AFRH_AFSEL10_Pos;
    GPIOC->AFR[1] |= GPIO_AF1_USART3<<GPIO_AFRH_AFSEL11_Pos;
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    USART3->BRR = HAL_RCC_GetHCLKFreq()/115200;
    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;
    USART3->CR1 |= USART_CR1_UE;
}

void TRANSMIT_CHARACTER(char myChar){
    while(!(USART3->ISR & (1 << 7))){
    }
    USART3->TDR = myChar;
}
void Transmit_String(char myString[]){
    for(int i = 0; i < strlen(myString); i++) {
        TRANSMIT_CHARACTER(myString[i]);
    }
}
void Keystroke_Led_Toggle(){
     GPIO_InitTypeDef initStr = {GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6, GPIO_MODE_OUTPUT_PP, GPIO_SPEED_FREQ_LOW, GPIO_NOPULL};
    My_HAL_GPIO_Init(GPIOC, &initStr);
    Transmit_String("Input color: r for red, b for blue, g for green, o for orange \n");
    while(!(USART3->ISR & (1 << 5))){
    }
    char myChar = USART3->RDR;
    if (myChar != 'r' && myChar != 'b' && myChar != 'g' && myChar != 'o'){
        Transmit_String("Invalid color \n");
        
        return;
    }
    Transmit_String("Input mode: 0 for off, 1 for on , 2 for toggle \n");
    while(!(USART3->ISR & (1 <<5))){
    }
    char func = USART3->RDR;
    if (func != '0' && func != '1' && func != '2'){
        Transmit_String("Invalid mode \n");
        return;
    }

    if(myChar == 'r'){
        if(func == '0'){
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, 0);
            Transmit_String("You turned off red \n");
        }
        else if (func == '1') {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
            Transmit_String("You turned on red \n");
        }
        else if (func == '2') {
            My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
            Transmit_String("You toggled red \n");
        }

    }
    else if(myChar == 'b'){
        if(func == '0'){
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, 0);
            Transmit_String("You turned off blue \n");
        }
        else if (func == '1') {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
            Transmit_String("You turned on blue \n");
        }
        else if (func == '2') {
            My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
            Transmit_String("You toggled blue \n");
        }

    }
    else if(myChar == 'o'){
        if(func == '0'){
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 0);
            Transmit_String("You turned off orange \n");

        }
        else if (func == '1') {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
            Transmit_String("You turned on orange \n");

        }
        else if (func == '2') {
            My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
            Transmit_String("You toggled orange \n");

        }

    }
    else if(myChar == 'g'){
        if(func == '0'){
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, 0);
            Transmit_String("You turned off green \n");

        }
        else if (func == '1') {
            My_HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
            Transmit_String("You turned on green \n");
        }
        else if (func == '2') {
            My_HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
            Transmit_String("You toggled green \n");
        }

    }
    else{
        Transmit_String("That is not a valid character \n");
    }

}

