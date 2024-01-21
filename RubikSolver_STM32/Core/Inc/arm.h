/*
 * arm.h
 *
 *  Created on: Jan 17, 2024
 *      Author: Nhat Khai
 */

#ifndef INC_ARM_H_
#define INC_ARM_H_

#include <math.h>
#include <stdint.h>
#include "global.h"
#include "servo.h"

#define GRIPPER_MINIMUM 26				// in millimeters
#define GRIPPER_MAXIMUM 44				// in millimeters
#define GRIPPER_CRANK 15				// in millimeters
#define GRIPPER_ROD 30					// in millimeters
#define GRIPPER_THICK 1.5				// in millimeters

#define WRIST_MINIMUM 0					// in degrees
#define WRIST_MAXIMUM 180				// in degrees

#define ELBOW_MINIMUM 0					// in millimeters
#define ELBOW_MAXIMUM 25				// in millimeters
#define ELBOW_CRANK 15					// in millimeters
#define ELBOW_ROD 20					// in millimeters
#define ELBOW_OFFSET 20					// in millimeters

#define ARM_NUMBER 4
#define ARM_UNDEFINED ARM_NUMBER

#define ARM_HOLD 55
#define ARM_RELEASE 65
#define ARM_RELAX 85

#define ARM_WESTWARD 180
#define ARM_NORTHWEST 135
#define ARM_NORTHWARD 90
#define ARM_NORTHEAST 45
#define ARM_EASTWARD 0

#define ARM_FORWARD 25
#define ARM_BACKWARD 5

typedef struct {
	uint8_t gripperID;
	uint8_t wristID;
	uint8_t elbowID;
	float distance;
	float degree;
	float location;
} arm;

extern arm arms[ARM_NUMBER];

void armInit(void);
uint8_t armStart(uint8_t gripperID, uint8_t wristID, uint8_t elbowID);

void armRun(void);
void armGrip(arm *armPointer);
void armRotate(arm *armPointer);
void armMove(arm *armPointer);

void armHold(arm *armPointer);
void armRelease(arm *armPointer);
void armRelax(arm *armPointer);

void armWestward(arm *armPointer);
void armNorthwest(arm *armPointer);
void armNorthward(arm *armPointer);
void armNortheast(arm *armPointer);
void armEastward(arm *armPointer);

void armForward(arm *armPointer);
void armBackward(arm *armPointer);

#endif /* INC_ARM_H_ */
