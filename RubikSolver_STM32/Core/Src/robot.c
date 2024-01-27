/*
 * robot.c
 *
 *  Created on: Jan 17, 2024
 *      Author: Nhat Khai
 */

#include "robot.h"

static uint8_t leftGripper = SERVO_UNDEFINED;
static uint8_t frontGripper = SERVO_UNDEFINED;
static uint8_t rightGripper = SERVO_UNDEFINED;
static uint8_t backGripper = SERVO_UNDEFINED;

static uint8_t leftWrist = SERVO_UNDEFINED;
static uint8_t frontWrist = SERVO_UNDEFINED;
static uint8_t rightWrist = SERVO_UNDEFINED;
static uint8_t backWrist = SERVO_UNDEFINED;

static uint8_t leftElbow = SERVO_UNDEFINED;
static uint8_t frontElbow = SERVO_UNDEFINED;
static uint8_t rightElbow = SERVO_UNDEFINED;
static uint8_t backElbow = SERVO_UNDEFINED;

static uint8_t leftArm = ARM_UNDEFINED;
static uint8_t frontArm = ARM_UNDEFINED;
static uint8_t rightArm = ARM_UNDEFINED;
static uint8_t backArm = ARM_UNDEFINED;

static robotState state;
static robotMovingArm movingArm;
static robotFlippingArm flippingArm;

void robotFree(void)
{
	state = FREE;
	movingArm.armID = ARM_UNDEFINED;
	flippingArm.firstArmID = ARM_UNDEFINED;
	flippingArm.secondArmID = ARM_UNDEFINED;
}

void robotInit(void)
{
	state = INIT;
	movingArm.armID = ARM_UNDEFINED;
	flippingArm.firstArmID = ARM_UNDEFINED;
	flippingArm.secondArmID = ARM_UNDEFINED;

	servoInit();
	armInit();

	leftGripper = servoStart(&htim2, TIM_CHANNEL_1, 0);
	frontGripper = servoStart(&htim2, TIM_CHANNEL_2, 0);
	rightGripper = servoStart(&htim2, TIM_CHANNEL_3, 0);
	backGripper = servoStart(&htim2, TIM_CHANNEL_4, -7);

	leftWrist = servoStart(&htim3, TIM_CHANNEL_1, -7);
	frontWrist = servoStart(&htim3, TIM_CHANNEL_2, 0);
	rightWrist = servoStart(&htim3, TIM_CHANNEL_3, 0);
	backWrist = servoStart(&htim3, TIM_CHANNEL_4, -5);

	leftElbow = servoStart(&htim4, TIM_CHANNEL_1, 0);
	frontElbow = servoStart(&htim4, TIM_CHANNEL_2, 0);
	rightElbow = servoStart(&htim4, TIM_CHANNEL_3, 0);
	backElbow = servoStart(&htim4, TIM_CHANNEL_4, 0);

	leftArm = armStart(leftGripper, leftWrist, leftElbow);
	frontArm = armStart(frontGripper, frontWrist, frontElbow);
	rightArm = armStart(rightGripper, rightWrist, rightElbow);
	backArm = armStart(backGripper, backWrist, backElbow);
}

void robotBoot(void)
{
	HAL_Delay(1000);
	servoRun();
	HAL_Delay(1000);
	armRun();
	HAL_Delay(3000);
	armRelease(&arms[rightArm]);
	HAL_Delay(2000);
	armHold(&arms[rightArm]);
	HAL_Delay(2000);
	armForward(&arms[rightArm]);
	HAL_Delay(2000);
	armForward(&arms[leftArm]);
	HAL_Delay(2000);
	armForward(&arms[frontArm]);
	armForward(&arms[backArm]);
	HAL_Delay(2000);
	armHold(&arms[leftArm]);
	armHold(&arms[frontArm]);
	armHold(&arms[backArm]);
	HAL_Delay(1000);
	robotFree();
}

void robotMoveReturn(void)
{
	HAL_Delay(1000);
	armRelease(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armBackward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armNorthward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armForward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armHold(&arms[movingArm.armID]);
	HAL_Delay(1000);
	robotFree();
}

void robotMoveNormal(void)
{
	if (state != FREE) return;
	state = BUSY;
	HAL_Delay(1000);
	armEastward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	robotMoveReturn();
}

void robotMoveInvert(void)
{
	if (state != FREE) return;
	state = BUSY;
	HAL_Delay(1000);
	armWestward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	robotMoveReturn();
}

void robotMoveDouble(void)
{
	if (state != FREE) return;
	state = BUSY;
	HAL_Delay(1000);
	armRelease(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armBackward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armEastward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armForward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armHold(&arms[movingArm.armID]);
	HAL_Delay(1000);
	armWestward(&arms[movingArm.armID]);
	HAL_Delay(1000);
	robotMoveReturn();
}

void robotMoveLeftNormal(void)
{
	movingArm.armID = leftArm;
	robotMoveNormal();
}

void robotMoveLeftInvert(void)
{
	movingArm.armID = leftArm;
	robotMoveInvert();
}

void robotMoveLeftDouble(void)
{
	movingArm.armID = leftArm;
	robotMoveDouble();
}

void robotMoveFrontNormal(void)
{
	movingArm.armID = frontArm;
	robotMoveNormal();
}

void robotMoveFrontInvert(void)
{
	movingArm.armID = frontArm;
	robotMoveInvert();
}

void robotMoveFrontDouble(void)

{
	movingArm.armID = frontArm;
	robotMoveDouble();
}

void robotMoveRightNormal(void) {
	movingArm.armID = rightArm;
	robotMoveNormal();
}

void robotMoveRightInvert(void)
{
	movingArm.armID = rightArm;
	robotMoveInvert();
}

void robotMoveRightDouble(void)
{
	movingArm.armID = rightArm;
	robotMoveDouble();
}

void robotMoveBackNormal(void)
{
	movingArm.armID = backArm;
	robotMoveNormal();
}

void robotMoveBackInvert(void)
{
	movingArm.armID = backArm;
	robotMoveInvert();
}

void robotMoveBackDouble(void)
{
	movingArm.armID = backArm;
	robotMoveDouble();
}

void robotFlipReturn(void)
{
	HAL_Delay(1000);
	armForward(&arms[flippingArm.thirdArmID]);
	armForward(&arms[flippingArm.fourthArmID]);
	HAL_Delay(1000);
	armHold(&arms[flippingArm.thirdArmID]);
	armHold(&arms[flippingArm.fourthArmID]);
	HAL_Delay(1000);
	armRelease(&arms[flippingArm.firstArmID]);
	armRelease(&arms[flippingArm.secondArmID]);
	HAL_Delay(1000);
	armBackward(&arms[flippingArm.firstArmID]);
	armBackward(&arms[flippingArm.secondArmID]);
	HAL_Delay(1000);
	armNorthward(&arms[flippingArm.firstArmID]);
	armNorthward(&arms[flippingArm.secondArmID]);
	HAL_Delay(1000);
	armForward(&arms[flippingArm.firstArmID]);
	armForward(&arms[flippingArm.secondArmID]);
	HAL_Delay(1000);
	armHold(&arms[flippingArm.firstArmID]);
	armHold(&arms[flippingArm.secondArmID]);
	robotFree();
}

void robotFlipNormal(void) {
	if (state != FREE) return;
	state = BUSY;
	HAL_Delay(1000);
	armRelease(&arms[flippingArm.thirdArmID]);
	armRelease(&arms[flippingArm.fourthArmID]);
	HAL_Delay(1000);
	armBackward(&arms[flippingArm.thirdArmID]);
	armBackward(&arms[flippingArm.fourthArmID]);
	HAL_Delay(1000);
	armEastward(&arms[flippingArm.firstArmID]);
	armWestward(&arms[flippingArm.secondArmID]);
	HAL_Delay(1000);
	robotFlipReturn();
}

void robotFlipInvert(void) {
	if (state != FREE) return;
	state = BUSY;
	HAL_Delay(1000);
	armRelease(&arms[flippingArm.thirdArmID]);
	armRelease(&arms[flippingArm.fourthArmID]);
	HAL_Delay(1000);
	armBackward(&arms[flippingArm.thirdArmID]);
	armBackward(&arms[flippingArm.fourthArmID]);
	HAL_Delay(1000);
	armWestward(&arms[flippingArm.firstArmID]);
	armEastward(&arms[flippingArm.secondArmID]);
	HAL_Delay(1000);
	robotFlipReturn();
}

void robotFlipXNormal(void)
{
	flippingArm.firstArmID = rightArm;
	flippingArm.secondArmID = leftArm;
	flippingArm.thirdArmID = frontArm;
	flippingArm.fourthArmID = backArm;
	robotFlipNormal();
}

void robotFlipXInvert(void)
{
	flippingArm.firstArmID = rightArm;
	flippingArm.secondArmID = leftArm;
	flippingArm.thirdArmID = frontArm;
	flippingArm.fourthArmID = backArm;
	robotFlipInvert();
}

void robotFlipZNormal(void)
{
	flippingArm.firstArmID = backArm;
	flippingArm.secondArmID = frontArm;
	flippingArm.thirdArmID = rightArm;
	flippingArm.fourthArmID = leftArm;
	robotFlipNormal();
}

void robotFlipZInvert(void)
{
	flippingArm.firstArmID = backArm;
	flippingArm.secondArmID = frontArm;
	flippingArm.thirdArmID = rightArm;
	flippingArm.fourthArmID = leftArm;
	robotFlipInvert();
}

void robotReadColorInit(void)
{
	HAL_Delay(1000);
	armRelax(&arms[rightArm]);
	HAL_Delay(1000);
	armEastward(&arms[rightArm]);
}

void robotReadColor(uint8_t step)
{
	arm readColorArm = arms[rightArm];
	switch (step)
	{
	case 0:
		HAL_Delay(1000);
		armNortheast(&readColorArm);
		break;
	case 1:
		HAL_Delay(1000);
		armNorthward(&readColorArm);
		break;
	case 2:
		HAL_Delay(1000);
		armNorthwest(&readColorArm);
		break;
	case 3:
		HAL_Delay(1000);
		armWestward(&readColorArm);
		HAL_Delay(1000);
		armHold(&readColorArm);
		HAL_Delay(1000);
		armEastward(&readColorArm);
		HAL_Delay(1000);
		armRelax(&readColorArm);
		break;
	case 4:
		HAL_Delay(1000);
		armNortheast(&readColorArm);
		break;
	case 5:
		HAL_Delay(1000);
		armNorthward(&readColorArm);
		break;
	case 6:
		HAL_Delay(1000);
		armNorthwest(&readColorArm);
		break;
	case 7:
		HAL_Delay(1000);
		armWestward(&readColorArm);
		HAL_Delay(1000);
		armHold(&readColorArm);
		HAL_Delay(1000);
		armEastward(&readColorArm);
		HAL_Delay(1000);
		armRelax(&readColorArm);
		HAL_Delay(1000);
		armNorthward(&readColorArm);
		HAL_Delay(1000);
		armHold(&readColorArm);
		break;
	}
}

uint8_t i = 0;
void robotTest(void)
{
	uint8_t j = leftGripper;
	if (i == 0)
	{
		servos[j].target = 45;
		i = 1;
	}
	else if (i == 1)
	{
		servos[j].target = 90;
		i = 2;
	}
	else if (i == 2)
	{
		servos[j].target = 0;
		i = 0;
	}
	else
	{
		i = 0;
	}
	servoRotate(&servos[j]);
}
