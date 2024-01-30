/*
 * color_reading.c
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#include "color_reading.h"

struct avg_color avg_colors[6];

float min(float a, float b)
{
	return (a > b ? b : a);
}

float diff(float a, float b)
{
	return (a > b ? a - b : b - a);
}

void readColor()
{
	for (uint8_t i = 0; i < NUM_COLOR_READ; ++i)
	{
		uint8_t rgb[3];
		readRGB(rgb, rgb + 1, rgb + 2);
		CDC_Transmit_FS(rgb, 3);
		HAL_Delay(USB_SPACE_DELAY);
	}
}

// Calculate an average rgb value of the colors
void colorCalculate(uint8_t color, uint8_t avg_colors[])
{
	uint32_t red_sum = 0;
	uint32_t blue_sum = 0;
	uint32_t green_sum = 0;
	for (uint16_t j = 0; j < NUM_COLOR_SETUP; ++j)
	{
		uint8_t colors[3] = {color, color, color};
		readRGB(colors, colors + 1, colors + 2);
		red_sum += colors[0];
		green_sum += colors[1];
		blue_sum += colors[2];
		HAL_Delay(COLOR_READING_DELAY);
	}
	avg_colors[0] = red_sum / NUM_COLOR_SETUP;
	avg_colors[1] = green_sum / NUM_COLOR_SETUP;
	avg_colors[2] = blue_sum / NUM_COLOR_SETUP;
}
