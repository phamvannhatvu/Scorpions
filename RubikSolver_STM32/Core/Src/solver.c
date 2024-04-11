/*
 * solver.c
 *
 *  Created on: Jan 5, 2024
 *      Author: ADMIN
 */

#include "solver.h"

uint8_t color_loaded = 0;
move solution[100];
uint8_t solution_len = 0;

/* Private functions*/

void addMoveToSolution(uint8_t* moves, uint8_t move_len)
{
	if (dataEqual(moves, move_len, "R"))
	{
		solution[solution_len] = R;
	}else if (dataEqual(moves, move_len, "R'"))
	{
		solution[solution_len] = RN;
	}else if (dataEqual(moves, move_len, "L"))
	{
		solution[solution_len] = L;
	}else if (dataEqual(moves, move_len, "L'"))
	{
		solution[solution_len] = LN;
	}else if (dataEqual(moves, move_len, "F"))
	{
		solution[solution_len] = F;
	}else if (dataEqual(moves, move_len, "F'"))
	{
		solution[solution_len] = FN;
	}else if (dataEqual(moves, move_len, "B"))
	{
		solution[solution_len] = B;
	}else if (dataEqual(moves, move_len, "B'"))
	{
		solution[solution_len] = BN;
	}else if (dataEqual(moves, move_len, "z"))
	{
		solution[solution_len] = z;
	}else if (dataEqual(moves, move_len, "z'"))
	{
		solution[solution_len] = zN;
	}
}

void turnByMove(move move)
{
	switch (move)
	{
	case R:
	{
		robotTurnRightNormal();
		break;
	}
	case RN:
	{
		robotTurnRightInvert();
		break;
	}
	case L:
	{
		robotTurnLeftNormal();
		break;
	}
	case LN:
	{
		robotTurnLeftInvert();
		break;
	}
	case F:
	{
		robotTurnFrontNormal();
		break;
	}
	case FN:
	{
		robotTurnFrontInvert();
		break;
	}
	case B:
	{
		robotTurnBackNormal();
		break;
	}
	case BN:
	{
		robotTurnBackInvert();
		break;
	}
	case z:
	{
		robotFlipZNormal();
		break;
	}
	case zN:
	{
		robotFlipZInvert();
		break;
	}
	default:
		break;
	}
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
		robotFlipXNormal();
		break;
	case 1:
		robotFlipXNormal();
		break;
	case 2:
		robotFlipXNormal();
		break;
	case 3:
		robotFlipXNormal();
		robotFlipZNormal();
		robotFlipXNormal();
		break;
	case 4:
		robotFlipXDouble();
		break;
	case 5:
		robotFlipXNormal();
		robotFlipZInvert();
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
	for (int i = 0; i < 48; ++i)
	{
		waitFromPC();
		readColor();
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
	// Set up initial state for the first face
	robotReadColorInit();
	for (int i = 0; i < 48; ++i)
	{
		readColor();
		waitFromPC();

		// After reading i-th cell color

		// Read next cell
		robotReadColor(i % 2);

		// Change face to read if current face reading is done
		if (i % 8 == 7)
		{
			// Set up condition for changing face
			robotChangeFaceInit();
			changeFaceToBeRead(i / 8);
			// Set up initial state for the new face
			if (i != 47) robotReadColorInit();
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
		addMoveToSolution(usb_buf, usb_len);
		uint8_t ack = 1;
		CDC_Transmit_FS(&ack, 1);
	}
	for (uint8_t i = 0; i < solution_len; ++i)
	{
		turnByMove(solution[i]);
		HAL_Delay(ROBOT_AUTODURATION);
	}
}
