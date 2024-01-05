/*
 * servo.c
 *
 *  Created on: Sep 7, 2023
 *      Author: ADMIN
 */
#include "servo.h"
#include "usbd_cdc_if.h"

const int ARM_OFFSET[4] = {0, 0, 0, 0};
const int HAND_OFFSET[4] = {0, 0, 0, 0};
const int GRIP_OFFSET[4] = {0, 0, 0, 0};
const int ARM_RATIO[4] = {1, 1, 1, 1};
const int HAND_RATIO[4] = {1, 1.5, 1, 1};
const int GRIP_RATIO[4] = {1, 1, 1, 1};

int arm_on_time[4] = {ZERO_DEGREE_ON_TIME, ZERO_DEGREE_ON_TIME,
		ZERO_DEGREE_ON_TIME, ZERO_DEGREE_ON_TIME};
int hand_on_time[4] = {ZERO_DEGREE_ON_TIME, ZERO_DEGREE_ON_TIME,
		ZERO_DEGREE_ON_TIME, ZERO_DEGREE_ON_TIME};
int grip_on_time[4] = {ZERO_DEGREE_ON_TIME, ZERO_DEGREE_ON_TIME,
		ZERO_DEGREE_ON_TIME, ZERO_DEGREE_ON_TIME};

GPIO_TypeDef *arm_port[4], *hand_port[4], *grip_port[4];
uint16_t arm_pin[4], hand_pin[4], grip_pin[4];

/* Private functions */
void rotate(int *rotate_part_on_time, float degree, int8_t offset, float weight_ratio)
{
	*rotate_part_on_time = ZERO_DEGREE_ON_TIME +
			(FULL_DEGREE_ON_TIME - ZERO_DEGREE_ON_TIME) *
			(weight_ratio * degree + offset) / 180.0;
}

float rad_to_deg(float rad)
{
	return rad * 180 / PI;
}

/* End of private functions */

void init_servo(GPIO_TypeDef **servo_port, uint16_t *servo_pin,
		GPIO_TypeDef *port, uint16_t pin)
{
	*servo_port = port;
	*servo_pin = pin;
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void arm_rotate(int index, float degree)
{
	rotate(&arm_on_time[index], degree, ARM_OFFSET[index], ARM_RATIO[index]);
}

void hand_rotate(int index, float degree)
{
	rotate(&hand_on_time[index], degree, HAND_OFFSET[index], HAND_RATIO[index]);
}

void grip_rotate(int index, float degree)
{
	rotate(&grip_on_time[index], degree, GRIP_OFFSET[index], GRIP_RATIO[index]);
}

void set_grip_dist(int index, float dist)
{
	float half_dist = dist;
	grip_rotate(index, acos((GRIP_L2*GRIP_L2 + half_dist*half_dist
		- GRIP_L1*GRIP_L1) / (2.0*GRIP_L2*half_dist)));
}

void set_arm_dist(int index, float dist)
{
	float real_dist = ARM_LEN * 2 - (MAX_POS - ARM_POS + dist);
	arm_rotate(index, rad_to_deg(acos(1 - real_dist / ARM_LEN)));
}

void test_servo()
{
//	arm_rotate(1, 90);
//	return;
//	for (int i = 0; i < 4; ++i)
//	{
//		arm_rotate(i, 0);
//		hand_rotate(i, 0);
//		grip_rotate(i, 0);
//	}
	hand_rotate(1, 90);
	HAL_Delay(1000);

	arm_rotate(1, 0);
	HAL_Delay(5000);

	hand_rotate(1, 0);
	HAL_Delay(5000);

//	for (int i = 0; i < 4; ++i)
//	{
//		arm_rotate(i, 90);
//		hand_rotate(i, 90);
//		grip_rotate(i, 90);
//	}

	arm_rotate(1, 90);
	HAL_Delay(1000);

	hand_rotate(1, 0);
	HAL_Delay(1000);
//	for (int i = 0; i < 4; ++i)
//	{
//		arm_rotate(i, 180);
//		hand_rotate(i, 180);
//		grip_rotate(i, 180);
//	}
//	HAL_Delay(1000);
}
