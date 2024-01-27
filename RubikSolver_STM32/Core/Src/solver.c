/*
 * solver.c
 *
 *  Created on: Jan 5, 2024
 *      Author: ADMIN
 */

#include "solver.h"

uint8_t color_loaded = 0;

/* Private functions*/

void turnByMove(uint8_t* moves, uint8_t move_len)
{
	if (dataEqual(moves, move_len, "R"))
	{
		robotMoveRightNormal();
	}else if (dataEqual(moves, move_len, "R'"))
	{
		robotMoveRightInvert();
	}else if (dataEqual(moves, move_len, "L"))
	{
		robotMoveLeftNormal();
	}else if (dataEqual(moves, move_len, "L'"))
	{
		robotMoveLeftInvert();
	}else if (dataEqual(moves, move_len, "F"))
	{
		robotMoveFrontNormal();
	}else if (dataEqual(moves, move_len, "F'"))
	{
		robotMoveFrontInvert();
	}else if (dataEqual(moves, move_len, "B"))
	{
		robotMoveBackNormal();
	}else if (dataEqual(moves, move_len, "B'"))
	{
		robotMoveBackInvert();
	}else if (dataEqual(moves, move_len, "z"))
	{
		robotFlipZNormal();
	}else if (dataEqual(moves, move_len, "z'"))
	{
		robotFlipZInvert();
	}
}

void loadColor()
{
	uint8_t need_load = 1; // 1: need load, 0: not need load
	if (color_loaded == 0)
	{
		CDC_Transmit_FS(&need_load, 1);
		HAL_Delay(USB_SPACE_DELAY);
		// Read color from stored file
		for (int i = 0; i < 6; ++i)
		{
			uint8_t ack = 1;
			CDC_Transmit_FS(&ack, 1);
			HAL_Delay(USB_SPACE_DELAY);
			while (usb_received == 0 && usb_len != 3);
			usb_received = 0;
			setColorRange(i, usb_buf[0], usb_buf[1], usb_buf[2]);
		}
		color_loaded = 1;
	}else
	{
		need_load = 0;
		CDC_Transmit_FS(&need_load, 1);
		HAL_Delay(USB_SPACE_DELAY);
	}
}

void colorCalculate(uint8_t color, uint8_t avg_colors[])
{
	// Read color
	uint32_t red_sum = 0;
	uint32_t blue_sum = 0;
	uint32_t green_sum = 0;
	for (uint16_t j = 0; j < NUM_COLOR_SETUP; ++j)
	{
		uint8_t colors[3] = {color, color, color};
		// For test
//		readRGB(colors, colors + 1, colors + 2);
		red_sum += colors[0];
		green_sum += colors[1];
		blue_sum += colors[2];
		HAL_Delay(readColor_DELAY);
	}
	setColorRange(color, 1.0 * red_sum / NUM_COLOR_SETUP,
			1.0 * green_sum / NUM_COLOR_SETUP,
			1.0 * blue_sum / NUM_COLOR_SETUP);
	avg_colors[0] = red_sum / NUM_COLOR_SETUP;
	avg_colors[1] = green_sum / NUM_COLOR_SETUP;
	avg_colors[2] = blue_sum / NUM_COLOR_SETUP;
}

void waitFromPC()
{
	while (usb_received == 0);
	usb_received = 0;
	HAL_Delay(USB_SPACE_DELAY);
}

void changeFaceToBeRead(uint8_t face_index)
{
	switch (face_index)
	{
	case 0:
		robotFlipZNormal();
		break;
	case 1:
		robotFlipZNormal();
		break;
	case 2:
		robotFlipZNormal();
		break;
	case 3:
		robotFlipZNormal();
		robotFlipXNormal();
		robotFlipZNormal();
		break;
	case 4:
		robotFlipZNormal();
		robotFlipZNormal();
		break;
	case 5:
		robotFlipZNormal();
		robotFlipXInvert();
		break;
	}
}
/* End of private functions*/

void manualColorSetup()
{
	for (uint8_t i = 0; i < 6; ++i)
	{
		waitFromPC();
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		uint8_t avg_colors[3];
		colorCalculate(i, avg_colors);

		CDC_Transmit_FS(avg_colors, 3);
		HAL_Delay(USB_SPACE_DELAY);
	}
	color_loaded = 1;
}

void manualRubikSolve()
{
	loadColor();

	for (int i = 0; i < 48; ++i)
	{
		waitFromPC();
		enum color c = readColor();
		CDC_Transmit_FS((uint8_t*)&c, 1);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	}
}

void autoColorSetup()
{
	for (uint8_t i = 0; i < 6; ++i)
	{
		uint8_t avg_colors[3];
		colorCalculate(i, avg_colors);

		CDC_Transmit_FS(avg_colors, 3);
		HAL_Delay(USB_SPACE_DELAY);

		waitFromPC();
		changeFaceToBeRead(i);

	}
	color_loaded = 1;
}

void autoRubikSolve()
{
	loadColor();

	// Set up initial state for the first face
	robotReadColorInit();
	for (int i = 0; i < 48; ++i)
	{
		enum color cell_color = readColor();
		CDC_Transmit_FS((uint8_t*)&cell_color, 1);
		waitFromPC();

		// Read next cell
		robotReadColor(i % 8);

		// Change face to read if current face reading is done
		if (i % 8 == 7)
		{
			changeFaceToBeRead(i / 8);
			// Set up initial state for the new face
			robotReadColorInit();
		}

	}

	uint8_t start_solving = 1;
	CDC_Transmit_FS(&start_solving, 1);
	// Turn the cube according to the solution's moves
	while (1)
	{
		waitFromPC();
		if (dataEqual(usb_buf, usb_len, "done"))
		{
			break;
		}
		turnByMove(usb_buf, usb_len);
		uint8_t ack = 1;
		CDC_Transmit_FS(&ack, 1);
	}
}
