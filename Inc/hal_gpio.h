#include <stdint.h>
#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_gpio.h>

void My_HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void My_HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
void My_HAL_RCC_GPIOC_CLK_ENABLE(void);
void EXTI0_1_IRQHandler(void);
GPIO_PinState My_HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void My_HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void My_HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void My_HAL_RCC_GPIOC_CLK_ENABLE(void);
void SYSCONFIG_ROUTE_PA0_EXTI0(void);
void EXTI_INTERRUPT(void);
void SystemClock_Config(void);
void My_HAL_TIMED_TogglePin();
void TIM2_IRQHandler(void);
void My_HAL_DIM_LED_TIM3(void);
void CREATE_TRANSMIT_RECEIVE(void);



