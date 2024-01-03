/*
 * color_reading.c
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#include "color_reading.h"
#include "usbd_cdc_if.h"

void color_setup()
{
	while (usb_received == 0);
	usb_received = 0;
	while (data_equal(usb_buf, 11, "color_setup") == 0)
	{
		while (usb_received == 0);
		usb_received = 0;
	}
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	for (uint8_t i = 0; i < 6; ++i)
	{
		while (usb_received == 0);
		usb_received = 0;
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

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
