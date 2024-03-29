/*
 * helper.c
 *
 *  Created on: Sep 15, 2023
 *      Author: ADMIN
 */

#include "helper.h"

int dataEqual(uint8_t *data, uint8_t len, char *literal)
{
	if (len != strlen(literal)) return 0;
	for (uint8_t i = 0; i < len; ++i)
	{
		if (data[i] != literal[i]) return 0;
	}
	return 1;
}

uint8_t isClose(float a, float b)
{
	if ((a > b && a - b < EPSILON) || (a < b && b - a < EPSILON) || a == b)
	{
		return 1;
	}
	return 0;
}

float radToDeg(float rad)
{
	return rad * 180 / PI;
}


