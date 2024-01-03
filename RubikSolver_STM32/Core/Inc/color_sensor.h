/*
 * color_sensor.h
 *
 *  Created on: Sep 19, 2023
 *      Author: ADMIN
 */

#ifndef INC_COLOR_SENSOR_H_
#define INC_COLOR_SENSOR_H_

#include "global.h"

#define SENSOR_ADDR 0x52
#define ID_ADDR 0x12
#define COMMAND_BIT 0x80
#define EN_ADDR 0x00
#define READ_WORD 0x20
#define RDATAL 0x16
#define GDATAL 0x18
#define BDATAL 0x1A

#define READ_COLOR_DELAY 10
#define NUM_COLOR_SETUP 200
#define NUM_COLOR_READ 100
#define VALID_DIFF_STEP 15
#define MAX_DIFF 255

enum color{RED, WHITE, BLUE, GREEN, YELLOW, ORANGE, INVALID_COLOR};
struct avg_color
{
	float red;
	float green;
	float blue;
};

void color_sensor_init();
enum color read_color();
void set_color_range(enum color c, float red, float green, float blue);
void read_rgb(uint8_t *red, uint8_t *green, uint8_t *blue);

#endif /* INC_COLOR_SENSOR_H_ */
