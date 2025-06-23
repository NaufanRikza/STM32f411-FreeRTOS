#ifndef DRONE_PROPELLER_H
#define DRONE_PROPELLER_H

#include "stm32f4xx.h"

#define DRONE_PROPELLER_TIMER TIM1
#define DRONE_PROPELLER_MIN_SPEED 0 // Minimum speed in percentage (0%)
#define DRONE_PROPELLER_MAX_SPEED 100 // Maximum speed in percentage (100%)
#define DRONE_PROPELLER_PWM_FREQ 50 // PWM frequency in Hz (50 Hz for typical servos
#define DRONE_PROPELLER_DSHOT_FREQ 300000 // DShot frequency in Hz (300 kHz for DShot 600)
#define PWM_PROTOCOL // PWM protocol identifier
#define DRONE_PROPELLER_MIN_DUTYCYCLE_PERIOD 1000 // Minimum duty cycle period in microseconds (1000 us)
#define DRONE_PROPELLER_MAX_DUTYCYCLE_PERIOD 2000 // Maximum duty cycle period in microseconds (2000 us)

typedef enum 
{
    DRONE_PROPELLER_FRONT_RIGHT = 0x00,
    DRONE_PROPELLER_FRONT_LEFT = 0x01,
    DRONE_PROPELLER_BACK_LEFT = 0x02,
    DRONE_PROPELLER_BACK_RIGHT = 0x03,
} DronePropellerChannel_t;

typedef struct 
{
    uint8_t ID ; //Propeller ID
    int Pin; //GPIO pin number
    TIM_TypeDef *PropellerTimer; //Timer used for PWM
    uint32_t Channel; //Timer channel used for PWM
    uint32_t PWMPeriod; //PWM period in microseconds
    uint32_t MaxDutycyclePeriod; //maximum period in microseconds
    uint32_t MinDutycyclePeriod; //minimum period in microseconds
    uint32_t CurrentDutycyclePeriode; //current period in microseconds
} DronePropeller_t;

DronePropeller_t *drone_propeller_array[4];
uint16_t drone_propeller_length;
TIM_HandleTypeDef drone_propeller_timer;

void drone_propeller_init(DronePropeller_t *propeller);
void drone_propeller_set_speed(DronePropellerChannel_t channel, uint32_t speed);
void drone_propeller_start();

#endif