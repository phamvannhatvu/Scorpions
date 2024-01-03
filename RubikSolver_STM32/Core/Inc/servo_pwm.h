/*
 * servo_pwm.h
 *
 *  Created on: Jan 3, 2024
 *      Author: ADMIN
 */

#ifndef INC_SERVO_PWM_H_
#define INC_SERVO_PWM_H_

#include "global.h"

enum SERVO_STATUS
{
	ON,
	OFF
};

void servos_pwm_timer_run();

#endif /* INC_SERVO_PWM_H_ */
