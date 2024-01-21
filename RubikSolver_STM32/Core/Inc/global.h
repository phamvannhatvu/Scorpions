/*
 * global.h
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "main.h"

extern I2C_HandleTypeDef hi2c2;
extern uint8_t usb_buf[200];
extern uint8_t usb_len;
extern uint8_t usb_received;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
#endif
