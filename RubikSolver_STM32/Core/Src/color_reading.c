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

void setColorRange(enum color c, float red, float green, float blue)
{
	avg_colors[c].red = red;
	avg_colors[c].green = green;
	avg_colors[c].blue = blue;
}

enum color readColor()
{
	for (uint8_t valid_diff = 0; valid_diff < MAX_DIFF; valid_diff += VALID_DIFF_STEP)
	{
		uint32_t red_sum = 0;
		uint32_t blue_sum = 0;
		uint32_t green_sum = 0;
		for (uint8_t i = 0; i < NUM_COLOR_READ; ++i)
		{
			uint8_t red, green, blue;
			readRGB(&red, &green, &blue);
			red_sum += red;
			green_sum += green;
			blue_sum += blue;
		}

		float red_avg = 1.0 * red_sum / NUM_COLOR_READ;
		float green_avg = 1.0 * green_sum / NUM_COLOR_READ;
		float blue_avg = 1.0 * blue_sum / NUM_COLOR_READ;

		for (uint8_t i = 0; i < 6; ++i)
		{
			if (diff(red_avg, avg_colors[i].red) <= valid_diff
					&& diff(green_avg, avg_colors[i].green) <= valid_diff
					&& diff(blue_avg, avg_colors[i].blue) <= valid_diff)
			{
				return i;
			}
		}
	}

	return INVALID_COLOR;
}
