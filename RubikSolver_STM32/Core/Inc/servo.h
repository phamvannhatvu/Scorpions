/*
 * servo.h
 *
 *  Created on: Sep 7, 2023
 *      Author: ADMIN
 */
#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "math.h"
#include "main.h"

#define PI acos(-1)

#define ZERO_DEGREE_ON_TIME 250
#define FULL_DEGREE_ON_TIME 1250

#define GRIP_HOLD_DEGREE 3
#define GRIP_RELEASE_DEGREE 90

const extern int ARM_OFFSET[4];
const extern int HAND_OFFSET[4];
const extern int GRIP_OFFSET[4];
const extern int ARM_RATIO[4];
const extern int HAND_RATIO[4];
const extern int GRIP_RATIO[4];

extern TIM_HandleTypeDef arm_timer[4], hand_timer[4], grip_timer[4];
extern uint32_t arm_channel[4], hand_channel[4], grip_channel[4];

void arm_rotate(int index, float degree);
void hand_rotate(int index, float degree);
void grip_rotate(int index, float degree);
void set_grip_dist(int index, float dist);
void set_arm_dist(int index, float dist);

void init_servo(TIM_HandleTypeDef *servo_timer, uint32_t *servo_channel,
		TIM_HandleTypeDef timer, uint32_t channel);
void test_servo();

#endif /* INC_SERVO_H_ */
