/*
 * servo.c
 *
 *  Created on: Sep 7, 2023
 *      Author: ADMIN
 */
#include "servo.h"
#include "usbd_cdc_if.h"

// Index: RIGHT - FRONT - LEFT - BACK
const int ARM_OFFSET[4] = {0, 0, 0, 0};
const int HAND_OFFSET[4] = {0, 0, 0, 0};
const int GRIP_OFFSET[4] = {17, 0, 20, 0};
const int ARM_RATIO[4] = {1, 1, 1, 1};
const int HAND_RATIO[4] = {1, 1, 1, 1};
const int GRIP_RATIO[4] = {1, 1, 1, 1};

TIM_HandleTypeDef arm_timer[4], hand_timer[4], grip_timer[4];
uint32_t arm_channel[4], hand_channel[4], grip_channel[4];

/* Private functions */
void rotate(TIM_HandleTypeDef timer, uint32_t channel, float degree, int8_t offset, float weight_ratio)
{
	__HAL_TIM_SetCompare(&timer, channel, ZERO_DEGREE_ON_TIME +
			(FULL_DEGREE_ON_TIME - ZERO_DEGREE_ON_TIME) *
			(weight_ratio * degree + offset) / 180.0);
}

void grip_rotate(int index, float degree)
{
	rotate(grip_timer[index], grip_channel[index], degree, GRIP_OFFSET[index], GRIP_RATIO[index]);
}
/* End of private functions */

float rad_to_deg(float rad)
{
	return rad * 180 / PI;
}

/* End of private functions */

void init_servo(TIM_HandleTypeDef *servo_timer, uint32_t *servo_channel,
		TIM_HandleTypeDef timer, uint32_t channel)
{
	*servo_timer = timer;
	*servo_channel = channel;
}

void arm_rotate(int index, float degree)
{
	rotate(arm_timer[index], arm_channel[index], degree, ARM_OFFSET[index], ARM_RATIO[index]);
}

void hand_rotate(int index, float degree)
{
	rotate(hand_timer[index], hand_channel[index], degree, HAND_OFFSET[index], HAND_RATIO[index]);
}

void grip_hold(int index, float degree)
{
	grip_rotate(index, GRIP_HOLD_DEGREE);
}

void grip_release(int index, float degree)
{
	grip_rotate(index, GRIP_RELEASE_DEGREE);
}

void test_servo()
{

}
