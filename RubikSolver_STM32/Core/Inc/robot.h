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

#define ROBOT_MANUALDURATION 2999
#define ROBOT_AUTODURATION 499

#define ROBOT_BOOT (9 * ROBOT_MANUALDURATION)
#define ROBOT_TURNSINGLE (10 * ROBOT_AUTODURATION)
#define ROBOT_TURNDOUBLE (12 * ROBOT_AUTODURATION)
#define ROBOT_FLIPSINGLE (11 * ROBOT_AUTODURATION)
#define ROBOT_FLIPDOUBLE (16 * ROBOT_AUTODURATION)

typedef enum {
	INIT,
	FREE,
	BUSY
} robotState;

typedef struct {
	uint8_t armID;
} robotTurningArm;

typedef struct {
	uint8_t firstArmID;
	uint8_t secondArmID;
	uint8_t thirdArmID;
	uint8_t fourthArmID;
} robotFlippingArm;

void robotInit(void);
void robotShutDown(void);
void robotBoot(void);

void robotTurnLeftNormal(void);
void robotTurnLeftInvert(void);
void robotTurnLeftDouble(void);
void robotTurnFrontNormal(void);
void robotTurnFrontInvert(void);
void robotTurnFrontDouble(void);
void robotTurnRightNormal(void);
void robotTurnRightInvert(void);
void robotTurnRightDouble(void);
void robotTurnBackNormal(void);
void robotTurnBackInvert(void);
void robotTurnBackDouble(void);

void robotFlipXNormal(void);
void robotFlipXInvert(void);
void robotFlipXDouble(void);
void robotFlipZNormal(void);
void robotFlipZInvert(void);
void robotFlipZDouble(void);

void robotReadColorInit(void);
void robotReadColor(uint8_t step);
void robotReadColorInit(void);
void robotChangeFaceInit(void);
void robotTest(void);

#endif /* INC_ROBOT_H_ */
