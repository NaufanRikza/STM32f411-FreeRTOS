#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include "stm32f4xx_hal.h"
#include "drone_propeller.h"

#define LED_PIN1 GPIO_PIN_13
#define LED_PIN2 GPIO_PIN_12
#define BUILTIN_LED GPIO_PIN_13

DronePropeller_t propellerFR, propellerFL, propellerBL, propellerBR;

void Error_Handler(void);
void SystemClock_Config(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void systemInit(void);
void gpio_init(void);
void propellers_init(void);

#endif