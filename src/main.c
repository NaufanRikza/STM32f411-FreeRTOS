/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

osThreadId_t led1_task_handler;
osThreadId_t led2_task_handler;
osThreadId_t led3_task_handler;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

void led1_task(void *argument);
void led2_task(void *argument);
void led3_task(void *argument);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  systemInit();
  /* Init scheduler */
  osKernelInitialize();
  // /* creation of defaultTask */
  led1_task_handler = osThreadNew(led1_task, NULL, &defaultTask_attributes);
  led2_task_handler = osThreadNew(led2_task, NULL, &defaultTask_attributes);
  led3_task_handler = osThreadNew(led3_task, NULL, &defaultTask_attributes);

  // /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  while (1)
  {

  }
}

 void led1_task(void *argument)
 {
   for(;;)
   {
    HAL_GPIO_WritePin(GPIOB, LED_PIN1, GPIO_PIN_SET); // Set PA5 high
    osDelay(1500); // Delay for 1 second
    HAL_GPIO_WritePin(GPIOB, LED_PIN1, GPIO_PIN_RESET); // Set PA5 low
    osDelay(1500); // Delay for 1 second
   }
 }

 void led2_task(void *argument)
 {
   for(;;)
   {
    HAL_GPIO_WritePin(GPIOB, LED_PIN2, GPIO_PIN_SET); // Set PA5 high
    osDelay(100); // Delay for 1 second
    HAL_GPIO_WritePin(GPIOB, LED_PIN2, GPIO_PIN_RESET); // Set PA5 low
    osDelay(100); // Delay for 1 second
   }
 }

  void led3_task(void *argument)
  {
    for(;;)
    {
      HAL_GPIO_WritePin(GPIOC, BUILTIN_LED, GPIO_PIN_SET); // Set PA5 high
      osDelay(500); // Delay for 1 second
      HAL_GPIO_WritePin(GPIOC, BUILTIN_LED, GPIO_PIN_RESET); // Set PA5 low
      osDelay(500); // Delay for 1 second
    }
  }

