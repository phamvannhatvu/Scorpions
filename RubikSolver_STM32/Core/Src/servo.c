/*
 * servo.c
 *
 *  Created on: Jan 16, 2024
 *      Author: Nhat Khai
 */

#include "servo.h"

servo servos[SERVO_NUMBER];

void servoInit(void)
{
	for (uint8_t i = 0; i < SERVO_NUMBER; i ++)
	{
		servos[i].timer = NULL;
		servos[i].channel = 0;
		servos[i].offset = 0;
		servos[i].target = 0;
	}
}

uint8_t servoStart(TIM_HandleTypeDef *timer, uint32_t channel, float offset)
{
	for (uint8_t i = 0; i < SERVO_NUMBER; i ++)
	{
		if (servos[i].timer != NULL) continue;
		servos[i].timer = timer;
		servos[i].channel = channel;
		if (offset < -SERVO_OFFSET) servos[i].offset = -SERVO_OFFSET;
		else if (offset > SERVO_OFFSET) servos[i].offset = SERVO_OFFSET;
		else servos[i].offset = offset;
		servos[i].target = 90;
		return i;
	}
	return SERVO_UNDEFINED;
}

void servoRun()
{
	for (uint8_t i = 0; i < SERVO_NUMBER; i ++)
	{
		if (servos[i].timer == NULL) continue;
		servoRotate(&servos[i]);
	}
}

void servoRotate(servo *servoPointer)
{
	if (servoPointer->timer == NULL) return;
	if (servoPointer->target < 0) servoPointer->target = 0;
	else if (servoPointer->target > 180) servoPointer->target = 180;
	uint32_t newValue = 1.0 * (servoPointer->timer->Instance->ARR + 1) / SERVO_PERIOD * (SERVO_MINIMUM + (SERVO_MAXIMUM - SERVO_MINIMUM) * (servoPointer->target + servoPointer->offset) / 180);
	//	newValue = newServoPointer->timer->Instance->ARR - newValue;
	__HAL_TIM_SET_COMPARE(servoPointer->timer, servoPointer->channel, newValue);
}
