/*
 * servo.c
 *
 *  Created on: Sep 7, 2023
 *      Author: ADMIN
 */
#include "servo.h"
#include "usbd_cdc_if.h"

int right_arm_on_time = ZERO_DEGREE_ON_TIME;
int right_hand_on_time = ZERO_DEGREE_ON_TIME;
int right_grip_on_time = ZERO_DEGREE_ON_TIME;
int front_arm_on_time = ZERO_DEGREE_ON_TIME;
int front_hand_on_time = ZERO_DEGREE_ON_TIME;
int front_grip_on_time = ZERO_DEGREE_ON_TIME;

GPIO_TypeDef *right_arm_port, *right_hand_port, *right_grip_port;
GPIO_TypeDef *front_arm_port, *front_hand_port, *front_grip_port;
uint16_t right_arm_pin, right_hand_pin, right_grip_pin;
uint16_t front_arm_pin, front_hand_pin, front_grip_pin;

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
		GPIO_TypeDef *port, uint16_t pin, float degree, void (*rotate)(float))
{
	*servo_port = port;
	*servo_pin = pin;
	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
	rotate(degree);
}

void right_arm_rotate(float degree)
{
	rotate(&right_arm_on_time, degree, RIGHT_ARM_OFFSET, RIGHT_ARM_RATIO);
}

void right_hand_rotate(float degree)
{
	rotate(&right_hand_on_time, degree, RIGHT_HAND_OFFSET, RIGHT_HAND_RATIO);
}

void right_grip_rotate(float degree)
{
	rotate(&right_grip_on_time, degree, RIGHT_GRIP_OFFSET, RIGHT_GRIP_RATIO);
}

void set_right_grip_dist(float dist)
{
	float half_dist = dist;
	right_grip_rotate(acos((GRIP_L2*GRIP_L2 + half_dist*half_dist - GRIP_L1*GRIP_L1) / (2.0*GRIP_L2*half_dist)));
}

void set_right_arm_dist(float dist)
{
	float real_dist = ARM_LEN * 2 - (MAX_POS - ARM_POS + dist);
	right_arm_rotate(rad_to_deg(acos(1 - real_dist / ARM_LEN)));
}

void front_arm_rotate(float degree)
{
	rotate(&front_arm_on_time, degree, FRONT_ARM_OFFSET, FRONT_ARM_RATIO);
}

void front_hand_rotate(float degree)
{
	rotate(&front_hand_on_time, degree, FRONT_HAND_OFFSET, FRONT_HAND_RATIO);
}

void front_grip_rotate(float degree)
{
	rotate(&front_grip_on_time, degree, FRONT_GRIP_OFFSET, FRONT_GRIP_RATIO);
}

void set_front_grip_dist(float dist)
{
	float half_dist = dist;
	front_grip_rotate(acos((GRIP_L2*GRIP_L2 + half_dist*half_dist - GRIP_L1*GRIP_L1) / (2.0*GRIP_L2*half_dist)));
}

void set_front_arm_dist(float dist)
{
	float real_dist = ARM_LEN * 2 - (MAX_POS - ARM_POS + dist);
	front_arm_rotate(rad_to_deg(acos(1 - real_dist / ARM_LEN)));
}

void test_servo()
{
	front_arm_rotate(0);
	HAL_Delay(2000);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	front_arm_rotate(90);
	HAL_Delay(2000);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	front_hand_rotate(90);
//	HAL_Delay(2000);
//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//	front_hand_rotate(0);
//	HAL_Delay(2000);
//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	front_arm_rotate(180);
	HAL_Delay(2000);
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}
