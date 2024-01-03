/*
 * servo_pwm.c
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#include "servo_pwm.h"
#include "usbd_cdc_if.h"

int right_arm_counter = 0;
int right_hand_counter = 0;
int right_grip_counter = 0;
int front_arm_counter = 0;
int front_hand_counter = 0;
int front_grip_counter = 0;

enum SERVO_STATUS right_arm_status = ON;
enum SERVO_STATUS right_hand_status = ON;
enum SERVO_STATUS right_grip_status = ON;
enum SERVO_STATUS front_arm_status = ON;
enum SERVO_STATUS front_hand_status = ON;
enum SERVO_STATUS front_grip_status = ON;

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
	servo_timer_run(&right_arm_counter, &right_arm_status,
			right_arm_port, right_arm_pin, right_arm_on_time);

	servo_timer_run(&right_hand_counter, &right_hand_status,
			right_hand_port, right_hand_pin, right_hand_on_time);

	servo_timer_run(&right_grip_counter, &right_grip_status,
			right_grip_port, right_grip_pin, right_grip_on_time);

	servo_timer_run(&front_arm_counter, &front_arm_status,
			front_arm_port, front_arm_pin, front_arm_on_time);

	servo_timer_run(&front_hand_counter, &front_hand_status,
			front_hand_port, front_hand_pin, front_hand_on_time);

	servo_timer_run(&front_grip_counter, &front_grip_status,
			front_grip_port, front_grip_pin, front_grip_on_time);
}
