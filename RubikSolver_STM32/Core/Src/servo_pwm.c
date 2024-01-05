/*
 * servo_pwm.c
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#include "servo_pwm.h"
#include "usbd_cdc_if.h"

// Right -> Front -> Left -> Back
int arm_counter[4] = {0, 0, 0, 0};
int hand_counter[4] = {0, 0, 0, 0};
int grip_counter[4] = {0, 0, 0, 0};

enum SERVO_STATUS arm_status[4] = {ON, ON, ON, ON};
enum SERVO_STATUS hand_status[4] = {ON, ON, ON, ON};
enum SERVO_STATUS grip_status[4] = {ON, ON, ON, ON};

void servo_timer_run(int *counter, enum SERVO_STATUS *status,
		GPIO_TypeDef* port, int pin, int on_time)
{
	--(*counter);
	if (*counter <= 0)
	{
		if (*status == ON)
		{
		  HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
		  *counter = SERVO_CYCLE - on_time;
		  *status = OFF;
		}else
		{
		  HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
		  *counter = on_time;
		  *status = ON;
		}
	}
}

void servos_pwm_timer_run()
{
	for (int i = 0; i < 4; ++i)
	{
		servo_timer_run(&arm_counter[i], &arm_status[i],
			arm_port[i], arm_pin[i], arm_on_time[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		servo_timer_run(&hand_counter[i], &hand_status[i],
			hand_port[i], hand_pin[i], hand_on_time[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		servo_timer_run(&grip_counter[i], &grip_status[i],
			grip_port[i], grip_pin[i], grip_on_time[i]);
	}
}
