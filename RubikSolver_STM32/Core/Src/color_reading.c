/*
 * color_reading.c
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#include "color_reading.h"
#include "usbd_cdc_if.h"

struct avg_color avg_colors[6];

float min(float a, float b)
{
	return (a > b ? b : a);
}

float diff(float a, float b)
{
	return (a > b ? a - b : b - a);
}

void set_color_range(enum color c, float red, float green, float blue)
{
	avg_colors[c].red = red;
	avg_colors[c].green = green;
	avg_colors[c].blue = blue;
}

void color_setup()
{
//	while (usb_received == 0);
//	usb_received = 0;
//	while (data_equal(usb_buf, 11, "color_setup") == 0)
//	{
//		while (usb_received == 0);
//		usb_received = 0;
//	}
//	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	for (uint8_t i = 0; i < 6; ++i)
	{
		// Waiting for user start reading
		while (usb_received == 0);
		usb_received = 0;
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		// Read color
		uint32_t red_sum = 0;
		uint32_t blue_sum = 0;
		uint32_t green_sum = 0;
		for (uint16_t j = 0; j < NUM_COLOR_SETUP; ++j)
		{
			uint8_t colors[3] = {0,0,0};
			read_rgb(colors, colors + 1, colors + 2);
			red_sum += colors[0];
			green_sum += colors[1];
			blue_sum += colors[2];
			HAL_Delay(READ_COLOR_DELAY);
		}
		set_color_range(i, 1.0 * red_sum / NUM_COLOR_SETUP,
				1.0 * green_sum / NUM_COLOR_SETUP,
				1.0 * blue_sum / NUM_COLOR_SETUP);
		uint8_t avg_colors[3] = {red_sum / NUM_COLOR_SETUP,
				green_sum / NUM_COLOR_SETUP,
				blue_sum / NUM_COLOR_SETUP};

		CDC_Transmit_FS(avg_colors, 3);
		HAL_Delay(USB_SPACE_DELAY);
	}
}


enum color read_color()
{
	for (uint8_t valid_diff = 0; valid_diff < MAX_DIFF; valid_diff += VALID_DIFF_STEP)
	{
		uint32_t red_sum = 0;
		uint32_t blue_sum = 0;
		uint32_t green_sum = 0;
		for (uint8_t i = 0; i < NUM_COLOR_READ; ++i)
		{
			uint8_t red, green, blue;
			read_rgb(&red, &green, &blue);
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
