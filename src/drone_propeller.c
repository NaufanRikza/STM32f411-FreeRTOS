#include "drone_propeller.h"

void drone_propeller_init(DronePropeller_t *propeller)
{
    #ifdef PWM_PROTOCOL
    propeller->PropellerTimer = DRONE_PROPELLER_TIMER; // Set the timer for PWM
    propeller->PWMPeriod = 1000000 / DRONE_PROPELLER_PWM_FREQ; // Calculate PWM period in microseconds
    #elif DSHOT_PROTOCOL
    propeller->PropellerTimer = DRONE_PROPELLER_TIMER; // Set the timer for DShot
    propeller->PWMPeriod = 1000000 / DRONE_PROPELLER_DSHOT_FREQ; // Calculate DShot period in microseconds
    #endif

    if (drone_propeller_length >= 4) {
        // Handle error: maximum number of propellers reached
        return; // or handle error appropriately
    }   
    drone_propeller_array[drone_propeller_length] = propeller; // Add to the array
    drone_propeller_length++; // Increment the count of propellerse
}

void drone_propeller_set_speed(DronePropellerChannel_t channel, uint32_t speed)
{
    // Ensure speed is within the defined range
    if (speed < DRONE_PROPELLER_MIN_SPEED || speed > DRONE_PROPELLER_MAX_SPEED) {
        return; // or handle error appropriately
    }

    DronePropeller_t *propeller = drone_propeller_array[channel]; // Get the propeller based on the channel
    if (propeller == NULL) {
        // Handle error: propeller not found
        return; // or handle error appropriately
    }

    // Calculate the duty cycle period based on the speed
    uint32_t speed_to_period = (uint32_t)((((speed * (propeller->MaxDutycyclePeriod - propeller->MinDutycyclePeriod)) / (float)(DRONE_PROPELLER_MAX_SPEED)) + propeller->MinDutycyclePeriod));
    if (speed_to_period < propeller->MinDutycyclePeriod) {
        speed_to_period = propeller->MinDutycyclePeriod; // Ensure it does not go below minimum
    } else if (speed_to_period > propeller->MaxDutycyclePeriod) {
        speed_to_period = propeller->MaxDutycyclePeriod; // Ensure it does not exceed maximum
    }
    propeller->CurrentDutycyclePeriode = speed_to_period; // Update current duty cycle period
    __HAL_TIM_SET_COMPARE(&drone_propeller_timer, propeller->Channel, speed_to_period); // Set the PWM duty cycle
}

void drone_propeller_start()
{
    __HAL_RCC_TIM1_CLK_ENABLE(); // Enable clock for TIM1
    __HAL_RCC_GPIOA_CLK_ENABLE(); // Enable clock for GPIOA
    // __HAL_TIM_MOE_ENABLE(&drone_propeller_timer);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // Initialize GPIO for each propeller
    uint32_t pins = 0;
    for (uint16_t i = 0; i < drone_propeller_length; i++) {
        DronePropeller_t *propeller = drone_propeller_array[i];
        pins |= propeller->Pin; // Combine all pins into a single variable
    }
    
    // Configure GPIO pins for output
    GPIO_InitStruct.Pin = pins;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP; // Alternate function push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // Set speed to low
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM1; // Set alternate function for TIM1
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize GPIOA with the configured settings

        // Initialize the timer for PWM
    drone_propeller_timer.Instance = DRONE_PROPELLER_TIMER;
    drone_propeller_timer.Init.Prescaler = 83; // Set frequency to 1 MHz (assuming 84 MHz clock)
    drone_propeller_timer.Init.CounterMode = TIM_COUNTERMODE_UP; // Count up
    // Set the period based on the PWM frequency
    drone_propeller_timer.Init.Period = drone_propeller_array[0]->PWMPeriod - 1; // Set period for PWM
    drone_propeller_timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // No clock division
    drone_propeller_timer.Init.RepetitionCounter = 0; // No repetition
    drone_propeller_timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE; // Disable auto-reload preload
    if (HAL_TIM_Base_Init(&drone_propeller_timer) != HAL_OK) {
        // Handle error: timer initialization failed
        return; // or handle error appropriately
    }

    TIM_OC_InitTypeDef sConfigOC = {0};
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;                      // Start with 0% duty cycle
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    for (uint16_t i = 0; i < drone_propeller_length; i++) {
        DronePropeller_t *propeller = drone_propeller_array[i];
        sConfigOC.Pulse = propeller->MinDutycyclePeriod;
        if (HAL_TIM_PWM_ConfigChannel(&drone_propeller_timer, &sConfigOC, propeller->Channel) != HAL_OK) {
            // Handle error: PWM configuration failed
            return; // or handle error appropriately
        }
        HAL_TIM_PWM_Start(&drone_propeller_timer, propeller->Channel); // Start PWM on the Channel
        // __HAL_TIM_SET_COMPARE(&drone_propeller_timer, propeller->Channel, propeller->MinDutycyclePeriod); // Set initial duty cycle
    }
}

