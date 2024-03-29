/*
 * helper.h
 *
 *  Created on: Sep 15, 2023
 *      Author: ADMIN
 */

#ifndef INC_HELPER_H_
#define INC_HELPER_H_

#include "global.h"
#include "string.h"
#include "math.h"

#define EPSILON 1e-4
#define PI acos(-1)

int dataEqual(uint8_t *data, uint8_t len, char *literal);
uint8_t isClose(float a, float b);
float radToDeg(float rad);

#endif /* INC_HELPER_H_ */
