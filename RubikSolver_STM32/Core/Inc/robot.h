/*
 * robot.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Nhat Khai
 */

#ifndef INC_ROBOT_H_
#define INC_ROBOT_H_

#include "global.h"
#include "arm.h"
#include "servo.h"

typedef enum {
	INIT,
	FREE,
	BUSY
} robotState;

typedef struct {
	uint8_t armID;
} robotMovingArm;

typedef struct {
	uint8_t firstArmID;
	uint8_t secondArmID;
	uint8_t thirdArmID;
	uint8_t fourthArmID;
} robotFlippingArm;

void robotInit(void);

void robotBoot(void);

void robotMoveLeftNormal(void);
void robotMoveLeftInvert(void);
void robotMoveLeftDouble(void);
void robotMoveFrontNormal(void);
void robotMoveFrontInvert(void);
void robotMoveFrontDouble(void);
void robotMoveRightNormal(void);
void robotMoveRightInvert(void);
void robotMoveRightDouble(void);
void robotMoveBackNormal(void);
void robotMoveBackInvert(void);
void robotMoveBackDouble(void);

void robotFlipXNormal(void);
void robotFlipXInvert(void);
void robotFlipZNormal(void);
void robotFlipZInvert(void);

void robotReadColorInit(void);
void robotReadColor(uint8_t step);

void robotTest(void);

#endif /* INC_ROBOT_H_ */
