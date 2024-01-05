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

#define ZERO_DEGREE_ON_TIME 3
#define FULL_DEGREE_ON_TIME 13.5
#define SERVO_CYCLE 100

#define GRIP_L1 30
#define GRIP_L2 15
#define ARM_LEN 20
#define ARM_POS 2.25
#define MAX_POS 10

const extern int ARM_OFFSET[4];
const extern int HAND_OFFSET[4];
const extern int GRIP_OFFSET[4];
const extern int ARM_RATIO[4];
const extern int HAND_RATIO[4];
const extern int GRIP_RATIO[4];

extern int arm_on_time[4];
extern int hand_on_time[4];
extern int grip_on_time[4];

extern GPIO_TypeDef *arm_port[4], *hand_port[4], *grip_port[4];
extern uint16_t arm_pin[4], hand_pin[4], grip_pin[4];

void arm_rotate(int index, float degree);
void hand_rotate(int index, float degree);
void grip_rotate(int index, float degree);
void set_grip_dist(int index, float dist);
void set_arm_dist(int index, float dist);

void init_servo(GPIO_TypeDef **servo_port, uint16_t *servo_pin,
		GPIO_TypeDef *port, uint16_t pin);
void test_servo();

#endif /* INC_SERVO_H_ */
