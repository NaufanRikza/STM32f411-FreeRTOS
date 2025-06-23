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
  // // /* creation of defaultTask */
  led1_task_handler = osThreadNew(led1_task, NULL, &defaultTask_attributes);

  // // /* Start scheduler */
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
      drone_propeller_set_speed(DRONE_PROPELLER_FRONT_RIGHT, 8); // Set speed to 50%
      osDelay(5000); // Delay for 1 second
      drone_propeller_set_speed(DRONE_PROPELLER_FRONT_RIGHT, 0); // Set speed to 50%
      osDelay(5000); // Delay for 1 second
      // drone_propeller_set_speed(DRONE_PROPELLER_FRONT_RIGHT, 60); // Set speed to 0%
      // osDelay(5000); // Delay for 1 second
      // drone_propeller_set_speed(DRONE_PROPELLER_FRONT_RIGHT, 80); // Set speed to 0%
      // osDelay(5000); // Delay for 1 second
      // drone_propeller_set_speed(DRONE_PROPELLER_FRONT_RIGHT, 100); // Set speed to 0%
      // osDelay(5000); // Delay for 1 second
   }
 }

