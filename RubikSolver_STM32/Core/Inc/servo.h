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

#define ZERO_DEGREE_ON_TIME 30
#define FULL_DEGREE_ON_TIME 135
#define SERVO_CYCLE 1000

#define RIGHT_GRIP_OFFSET 2
#define RIGHT_ARM_OFFSET -5
#define RIGHT_HAND_OFFSET -8
#define RIGHT_ARM_RATIO 1
#define RIGHT_HAND_RATIO 1
#define RIGHT_GRIP_RATIO 1

#define FRONT_GRIP_OFFSET 2
#define FRONT_ARM_OFFSET 0
#define FRONT_HAND_OFFSET 0
#define FRONT_ARM_RATIO 1
#define FRONT_HAND_RATIO 1.5
#define FRONT_GRIP_RATIO 1

#define GRIP_L1 30
#define GRIP_L2 15
#define ARM_LEN 20
#define ARM_POS 2.25
#define MAX_POS 10

extern int right_arm_on_time;
extern int right_hand_on_time;
extern int right_grip_on_time;
extern int front_arm_on_time;
extern int front_hand_on_time;
extern int front_grip_on_time;

extern GPIO_TypeDef *right_arm_port, *right_hand_port, *right_grip_port;
extern GPIO_TypeDef *front_arm_port, *front_hand_port, *front_grip_port;
extern uint16_t right_arm_pin, right_hand_pin, right_grip_pin;
extern uint16_t front_arm_pin, front_hand_pin, front_grip_pin;

void right_arm_rotate(float degree);
void right_hand_rotate(float degree);
void right_grip_rotate(float degree);
void set_right_grip_dist(float dist);
void set_right_arm_dist(float dist);

void front_arm_rotate(float degree);
void front_hand_rotate(float degree);
void front_grip_rotate(float degree);
void set_front_grip_dist(float dist);
void set_front_arm_dist(float dist);

void init_servo(GPIO_TypeDef **servo_port, uint16_t *servo_pin,
		GPIO_TypeDef *port, uint16_t pin, float degree, void (*rotate)(float));
void test_servo();

#endif /* INC_SERVO_H_ */
