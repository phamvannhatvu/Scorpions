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

#define USB_SPACE_DELAY 1000 //delay between consecutive usb transmit and receive

enum color{RED, WHITE, ORANGE, YELLOW, GREEN, BLUE, INVALID_COLOR};
struct avg_color
{
	float red;
	float green;
	float blue;
};

void color_setup();
enum color read_color();
void set_color_range(enum color c, float red, float green, float blue);

#endif /* INC_COLOR_READING_H_ */
