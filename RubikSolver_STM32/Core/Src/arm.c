/*
 * arm.c
 *
 *  Created on: Jan 17, 2024
 *      Author: Nhat Khai
 */

#include "arm.h"

arm arms[ARM_NUMBER];

void armInit(void)
{
	for (uint8_t i = 0; i < ARM_NUMBER; i ++)
	{
		arms[i].gripperID = SERVO_UNDEFINED;
		arms[i].wristID = SERVO_UNDEFINED;
		arms[i].elbowID = SERVO_UNDEFINED;
		arms[i].distance = 0;
		arms[i].degree = 0;
		arms[i].location = 0;
	}
}

uint8_t armStart(uint8_t gripperID, uint8_t wristID, uint8_t elbowID)
{
	for (uint8_t i = 0; i < ARM_NUMBER; i ++)
	{
		if (arms[i].gripperID != SERVO_UNDEFINED || arms[i].wristID != SERVO_UNDEFINED || arms[i].elbowID != SERVO_UNDEFINED) continue;
		arms[i].gripperID = gripperID;
		arms[i].wristID = wristID;
		arms[i].elbowID = elbowID;
		arms[i].distance = ARM_RELAX;
		arms[i].degree = ARM_NORTHWARD;
		arms[i].location = ARM_BACKWARD;
		return i;
	}
	return ARM_UNDEFINED;
}

void armRun(void)
{
	for (uint8_t i = 0; i < ARM_NUMBER; i ++)
	{
		if (arms[i].gripperID != SERVO_UNDEFINED)
		{
			armGrip(&arms[i]);
		}
		if (arms[i].wristID != SERVO_UNDEFINED)
		{
			armRotate(&arms[i]);
		}
		if (arms[i].elbowID != SERVO_UNDEFINED)
		{
			armMove(&arms[i]);
		}
	}
}

void armGrip(arm *armPointer)
{
	if (armPointer->gripperID == SERVO_UNDEFINED) return;
	float newDistance = armPointer->distance / 2.0 + GRIPPER_THICK;
	if (newDistance < GRIPPER_MINIMUM) newDistance = GRIPPER_MINIMUM;
	else if (newDistance > GRIPPER_MAXIMUM) newDistance = GRIPPER_MAXIMUM;
	float newTarget = 90 - acosf((powf(GRIPPER_CRANK, 2) + powf(newDistance, 2) - powf(GRIPPER_ROD, 2)) / (2 * GRIPPER_CRANK * newDistance)) / M_PI * 180.0;
	servos[armPointer->gripperID].target = newTarget;
	servoRotate(&servos[armPointer->gripperID]);
}

void armRotate(arm *armPointer)
{
	if (armPointer->wristID == SERVO_UNDEFINED) return;
	float newDegree = armPointer->degree;
	if (newDegree < WRIST_MINIMUM) newDegree = WRIST_MINIMUM;
	else if (newDegree > WRIST_MAXIMUM) newDegree = WRIST_MAXIMUM;
	float newTarget = newDegree;
	servos[armPointer->wristID].target = newTarget;
	servoRotate(&servos[armPointer->wristID]);
}

void armMove(arm *armPointer)
{
	if (armPointer->elbowID == SERVO_UNDEFINED) return;
	float newLocation = armPointer->location;
	if (newLocation < ELBOW_MINIMUM) newLocation = ELBOW_MINIMUM;
	else if (newLocation > ELBOW_MAXIMUM) newLocation = ELBOW_MAXIMUM;
	float tempValue = (powf(ELBOW_CRANK, 2) - powf(ELBOW_ROD, 2) + powf(ELBOW_OFFSET, 2) + powf(newLocation, 2)) / (2 * ELBOW_CRANK);
	float newTarget = 180 - (2 * atanf((ELBOW_OFFSET + sqrtf(powf(ELBOW_OFFSET, 2) + powf(newLocation, 2) - pow(tempValue, 2))) / (newLocation + tempValue)) / M_PI * 180.0);
	servos[armPointer->elbowID].target = newTarget;
	servoRotate(&servos[armPointer->elbowID]);
}

void armHold(arm *armPointer)
{
	armPointer->distance = ARM_HOLD;
	armGrip(armPointer);
}

void armRelease(arm *armPointer)
{
	armPointer->distance = ARM_RELEASE;
	armGrip(armPointer);
}

void armRelax(arm *armPointer)
{
	armPointer->distance = ARM_RELAX;
	armGrip(armPointer);
}

void armWestward(arm *armPointer)
{
	armPointer->degree = ARM_WESTWARD;
	armRotate(armPointer);
}

void armNorthwest(arm *armPointer)
{
	armPointer->degree = ARM_NORTHWEST;
	armRotate(armPointer);
}

void armNorthward(arm *armPointer)
{
	armPointer->degree = ARM_NORTHWARD;
	armRotate(armPointer);
}

void armNortheast(arm *armPointer)
{
	armPointer->degree = ARM_NORTHEAST;
	armRotate(armPointer);
}

void armEastward(arm *armPointer)
{
	armPointer->degree = ARM_EASTWARD;
	armRotate(armPointer);
}

void armForward(arm *armPointer)
{
	armPointer->location = ARM_FORWARD;
	armMove(armPointer);
}

void armBackward(arm *armPointer)
{
	armPointer->location = ARM_BACKWARD;
	armMove(armPointer);
}
