/*
 * robot.c
 *
 *  Created on: Jan 17, 2024
 *      Author: Nhat Khai
 */

#include "robot.h"

static uint8_t leftArm = ARM_UNDEFINED;
static uint8_t frontArm = ARM_UNDEFINED;
static uint8_t rightArm = ARM_UNDEFINED;
static uint8_t backArm = ARM_UNDEFINED;

static robotState state;
static robotTurningArm turningArm;
static robotFlippingArm flippingArm;

void robotFree(void)
{
	state = FREE;
	turningArm.armID = ARM_UNDEFINED;
	flippingArm.firstArmID = ARM_UNDEFINED;
	flippingArm.secondArmID = ARM_UNDEFINED;
}

void robotInit(void)
{
	state = INIT;
	turningArm.armID = ARM_UNDEFINED;
	flippingArm.firstArmID = ARM_UNDEFINED;
	flippingArm.secondArmID = ARM_UNDEFINED;

	servoInit();
	armInit();

	uint8_t leftGripper = servoStart(&htim2, TIM_CHANNEL_1, 5);
	uint8_t frontGripper = servoStart(&htim2, TIM_CHANNEL_2, 10);
	uint8_t rightGripper = servoStart(&htim2, TIM_CHANNEL_3, 0);
	uint8_t backGripper = servoStart(&htim2, TIM_CHANNEL_4, 0);

	uint8_t leftWrist = servoStart(&htim3, TIM_CHANNEL_1, -10);
	uint8_t frontWrist = servoStart(&htim3, TIM_CHANNEL_2, 0);
	uint8_t rightWrist = servoStart(&htim3, TIM_CHANNEL_3, -4);
	uint8_t backWrist = servoStart(&htim3, TIM_CHANNEL_4, 2);

	uint8_t leftElbow = servoStart(&htim4, TIM_CHANNEL_1, 0);
	uint8_t frontElbow = servoStart(&htim4, TIM_CHANNEL_2, 0);
	uint8_t rightElbow = servoStart(&htim4, TIM_CHANNEL_3, 0);
	uint8_t backElbow = servoStart(&htim4, TIM_CHANNEL_4, 10);

	leftArm = armStart(leftGripper, leftWrist, leftElbow);
	frontArm = armStart(frontGripper, frontWrist, frontElbow);
	rightArm = armStart(rightGripper, rightWrist, rightElbow);
	backArm = armStart(backGripper, backWrist, backElbow);
}

void robotBoot(void)
{
//	HAL_Delay(1000);
//	servoRun();
	HAL_Delay(ROBOT_MANUALDURATION);
	armRun();
	HAL_Delay(ROBOT_MANUALDURATION);
	armRelease(&arms[rightArm]);
	HAL_Delay(ROBOT_MANUALDURATION);
	armHold(&arms[rightArm]);
	HAL_Delay(ROBOT_MANUALDURATION);
	armForward(&arms[rightArm]);
	HAL_Delay(ROBOT_MANUALDURATION);
	armForward(&arms[leftArm]);
	HAL_Delay(ROBOT_MANUALDURATION);
	armForward(&arms[frontArm]);
	armForward(&arms[backArm]);
	HAL_Delay(ROBOT_MANUALDURATION);
	armHold(&arms[leftArm]);
	armHold(&arms[frontArm]);
	armHold(&arms[backArm]);
	HAL_Delay(ROBOT_MANUALDURATION);
	robotFree();
}

void robotShutDown(void) {
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[leftArm]);
	armRelease(&arms[frontArm]);
	armRelease(&arms[rightArm]);
	armRelease(&arms[backArm]);
	HAL_Delay(ROBOT_AUTODURATION);
	armBackward(&arms[leftArm]);
	armBackward(&arms[frontArm]);
	armBackward(&arms[rightArm]);
	armBackward(&arms[backArm]);
	HAL_Delay(ROBOT_AUTODURATION);
	armNorthward(&arms[leftArm]);
	armNorthward(&arms[frontArm]);
	armNorthward(&arms[rightArm]);
	armNorthward(&arms[backArm]);
	HAL_Delay(ROBOT_AUTODURATION);
	armRelax(&arms[leftArm]);
	armRelax(&arms[frontArm]);
	armRelax(&arms[rightArm]);
	armRelax(&arms[backArm]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotFree();
}

void robotTurnReturn(void)
{
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armBackward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armNorthward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armForward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotFree();
}

void robotTurnNormal(void)
{
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armFirstLayer(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armEastward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotTurnReturn();
}

void robotTurnInvert(void)
{
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armFirstLayer(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armWestward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotTurnReturn();
}

void robotTurnDouble(void)
{
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armBackward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armEastward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armForward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armWestward(&arms[turningArm.armID]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotTurnReturn();
}

void robotTurnLeftNormal(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = leftArm;
	robotTurnNormal();
}

void robotTurnLeftInvert(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = leftArm;
	robotTurnInvert();
}

void robotTurnLeftDouble(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = leftArm;
	robotTurnDouble();
}

void robotTurnFrontNormal(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = frontArm;
	robotTurnNormal();
}

void robotTurnFrontInvert(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = frontArm;
	robotTurnInvert();
}

void robotTurnFrontDouble(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = frontArm;
	robotTurnDouble();
}

void robotTurnRightNormal(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = rightArm;
	robotTurnNormal();
}

void robotTurnRightInvert(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = rightArm;
	robotTurnInvert();
}

void robotTurnRightDouble(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = rightArm;
	robotTurnDouble();
}

void robotTurnBackNormal(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = backArm;
	robotTurnNormal();
}

void robotTurnBackInvert(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = backArm;
	robotTurnInvert();
}

void robotTurnBackDouble(void)
{
	if (state != FREE) return;
	state = BUSY;
	turningArm.armID = backArm;
	robotTurnDouble();
}

void robotFlipReturn(void)
{
	HAL_Delay(ROBOT_AUTODURATION);
	armForward(&arms[flippingArm.thirdArmID]);
	armForward(&arms[flippingArm.fourthArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[flippingArm.thirdArmID]);
	armHold(&arms[flippingArm.fourthArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[flippingArm.firstArmID]);
	armRelease(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armBackward(&arms[flippingArm.firstArmID]);
	armBackward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armNorthward(&arms[flippingArm.firstArmID]);
	armNorthward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armForward(&arms[flippingArm.firstArmID]);
	armForward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[flippingArm.firstArmID]);
	armHold(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotFree();
}

void robotFlipSingle(void) {
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[flippingArm.thirdArmID]);
	armRelease(&arms[flippingArm.fourthArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armBackward(&arms[flippingArm.thirdArmID]);
	armBackward(&arms[flippingArm.fourthArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armEastward(&arms[flippingArm.firstArmID]);
	armWestward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotFlipReturn();
}

void robotFlipDouble(void) {
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[flippingArm.firstArmID]);
	armRelease(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armBackward(&arms[flippingArm.firstArmID]);
	armBackward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armWestward(&arms[flippingArm.firstArmID]);
	armEastward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armForward(&arms[flippingArm.firstArmID]);
	armForward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[flippingArm.firstArmID]);
	armHold(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armRelease(&arms[flippingArm.thirdArmID]);
	armRelease(&arms[flippingArm.fourthArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armBackward(&arms[flippingArm.thirdArmID]);
	armBackward(&arms[flippingArm.fourthArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	armEastward(&arms[flippingArm.firstArmID]);
	armWestward(&arms[flippingArm.secondArmID]);
	HAL_Delay(ROBOT_AUTODURATION);
	robotFlipReturn();
}

void robotFlipXNormal(void)
{
	if (state != FREE) return;
	state = BUSY;
	flippingArm.firstArmID = rightArm;
	flippingArm.secondArmID = leftArm;
	flippingArm.thirdArmID = frontArm;
	flippingArm.fourthArmID = backArm;
	robotFlipSingle();
}

void robotFlipXInvert(void)
{
	if (state != FREE) return;
	state = BUSY;
	flippingArm.firstArmID = leftArm;
	flippingArm.secondArmID = rightArm;
	flippingArm.thirdArmID = frontArm;
	flippingArm.fourthArmID = backArm;
	robotFlipSingle();
}

void robotFlipXDouble(void)
{
	if (state != FREE) return;
	state = BUSY;
	flippingArm.firstArmID = rightArm;
	flippingArm.secondArmID = leftArm;
	flippingArm.thirdArmID = frontArm;
	flippingArm.fourthArmID = backArm;
	robotFlipDouble();
}

void robotFlipZNormal(void)
{
	if (state != FREE) return;
	state = BUSY;
	flippingArm.firstArmID = frontArm;
	flippingArm.secondArmID = backArm;
	flippingArm.thirdArmID = rightArm;
	flippingArm.fourthArmID = leftArm;
	robotFlipSingle();
}

void robotFlipZInvert(void)
{
	if (state != FREE) return;
	state = BUSY;
	flippingArm.firstArmID = backArm;
	flippingArm.secondArmID = frontArm;
	flippingArm.thirdArmID = rightArm;
	flippingArm.fourthArmID = leftArm;
	robotFlipSingle();
}

void robotFlipZDouble(void)
{
	if (state != FREE) return;
	state = BUSY;
	flippingArm.firstArmID = frontArm;
	flippingArm.secondArmID = backArm;
	flippingArm.thirdArmID = rightArm;
	flippingArm.fourthArmID = leftArm;
	robotFlipDouble();
}

void robotReadColorInit(void)
{
	HAL_Delay(ROBOT_AUTODURATION);
	armRelax(&arms[frontArm]);
}

void robotChangeFaceInit(void)
{
	HAL_Delay(ROBOT_AUTODURATION);
	armHold(&arms[frontArm]);
}

void robotReadColor(uint8_t step)
{
	arm readColorArm = arms[frontArm];
	if (step == 0)
	{
		HAL_Delay(ROBOT_AUTODURATION);
		armNortheast(&readColorArm);
	}else
	{
		HAL_Delay(ROBOT_AUTODURATION);
		armNorthward(&readColorArm);
		HAL_Delay(ROBOT_AUTODURATION);
		armHold(&readColorArm);
		HAL_Delay(ROBOT_AUTODURATION);
		robotTurnFrontNormal();
		armRelax(&readColorArm);
	}
}

void robotTest(void)
{
	HAL_Delay(500);
	armRelax(&arms[frontArm]);
	HAL_Delay(500);
	armHold(&arms[frontArm]);
}
