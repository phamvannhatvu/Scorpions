/*
 * global.h
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#include "main.h"
#include "color_reading.h"
#include "servo.h"
#include "helper.h"
#include "solver.h"

extern I2C_HandleTypeDef hi2c1;
extern uint8_t usb_buf[200];
extern uint8_t usb_len;
extern uint8_t usb_received;
