/*
 * timer.c
 *
 *  Created on: Oct 21, 2023
 *      Author: ADMIN
 */
#include "timer.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	servos_pwm_timer_run();
}

