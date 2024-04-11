/*
 * color_reading.h
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#ifndef INC_COLOR_READING_H_
#define INC_COLOR_READING_H_

#include "global.h"
#include "color_sensor.h"
#include "usbd_cdc_if.h"

#define USB_SPACE_DELAY 1000 //delay between consecutive usb transmit and receive
#define NUM_COLOR_SETUP 100
#define NUM_COLOR_READ 100
#define VALID_DIFF_STEP 15
#define MAX_DIFF 255
#define COLOR_READING_DELAY 10

enum color{GREEN, YELLOW, BLUE, WHITE, RED, ORANGE, INVALID_COLOR};
struct avg_color
{
	float red;
	float green;
	float blue;
};

void readColor();
void setColorRange(enum color c, float red, float green, float blue);
void colorCalculate(uint8_t color, uint8_t avg_colors[]);

#endif /* INC_COLOR_READING_H_ */
