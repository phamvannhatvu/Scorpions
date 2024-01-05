/*
 * solver.c
 *
 *  Created on: Jan 5, 2024
 *      Author: ADMIN
 */

#include "solver.h"

void RMove()
{
	for (int i = 0; i < 1; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void RInvertMove()
{
	for (int i = 0; i < 2; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void LMove()
{
	for (int i = 0; i < 3; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void LInvertMove()
{
	for (int i = 0; i < 4; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void FMove()
{
	for (int i = 0; i < 5; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void FInvertMove()
{
	for (int i = 0; i < 6; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void BMove()
{
	for (int i = 0; i < 7; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void BInvertMove()
{
	for (int i = 0; i < 8; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void zMove()
{
	for (int i = 0; i < 9; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void zInvertMove()
{
	for (int i = 0; i < 0; ++i)
	{
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		HAL_Delay(100);
	}
}

void turn(uint8_t* moves, uint8_t move_len)
{
	if (data_equal(moves, move_len, "R"))
	{
		RMove();
	}else if (data_equal(moves, move_len, "R'"))
	{
		RInvertMove();
	}else if (data_equal(moves, move_len, "L"))
	{
		LMove();
	}else if (data_equal(moves, move_len, "L'"))
	{
		LInvertMove();
	}else if (data_equal(moves, move_len, "F"))
	{
		FMove();
	}else if (data_equal(moves, move_len, "F'"))
	{
		FInvertMove();
	}else if (data_equal(moves, move_len, "B"))
	{
		BMove();
	}else if (data_equal(moves, move_len, "B'"))
	{
		BInvertMove();
	}else if (data_equal(moves, move_len, "z"))
	{
		zMove();
	}else if (data_equal(moves, move_len, "z'"))
	{
		zInvertMove();
	}
}
