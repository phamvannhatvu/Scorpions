/*
 * color_sensor.c
 *
 *  Created on: Sep 19, 2023
 *      Author: ADMIN
 */


/*
 * color_sensor.c
 *
 *  Created on: Sep 15, 2023
 *      Author: ADMIN
 */

// Source code from: https://www.waveshare.com/wiki/TCS34725_Color_Sensor

#include "color_sensor.h"

void readI2CWord(uint8_t reg_addr, uint8_t *data)
{
	HAL_I2C_Mem_Read(&hi2c2, SENSOR_ADDR, COMMAND_BIT | READ_WORD | reg_addr, I2C_MEMADD_SIZE_8BIT, data, 2, 1000);
}

void readI2CByte(uint8_t reg_addr, uint8_t *data)
{
	HAL_I2C_Mem_Read(&hi2c2, SENSOR_ADDR, COMMAND_BIT | reg_addr, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
}

void writeI2CByte(uint8_t reg_addr, uint8_t *data)
{
	HAL_I2C_Mem_Write(&hi2c2, SENSOR_ADDR, COMMAND_BIT | reg_addr, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
}

void colorSensorInit()
{
	// Adjust sensor's LED brightness
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	__HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 500);
	uint8_t en[1] = {0xB};
	writeI2CByte(EN_ADDR, en);
	HAL_Delay(3);
}

void readRGB(uint8_t *red, uint8_t *green, uint8_t *blue)
{
	uint8_t reds[2] = {0x00, 0x00};
	uint8_t greens[2] = {0x00, 0x00};
	uint8_t blues[2] = {0x00, 0x00};

	readI2CWord(RDATAL, reds);
	readI2CWord(GDATAL, greens);
	readI2CWord(BDATAL, blues);
	HAL_Delay(3);

	uint16_t red16 = ((reds[1] << 8) + reds[0]);
	uint16_t green16 = ((greens[1] << 8) + greens[0]);
	uint16_t blue16 = ((blues[1] << 8) + blues[0]);

	float i = 1;
	//Limit data range
	if (red16 >= green16 && red16 >= blue16)
	{
		i = red16 / 255 + 1;
	}
	else if (green16 >= red16 && green16 >= blue16)
	{
		i = green16 / 255 + 1;
	}
	else if (blue16 >=  green16 && blue16 >= red16)
	{
		i = blue16 / 255 + 1;
	}
	if (i != 0)
	{
		red16 = (red16) / i;
		green16 = (green16) / i;
		blue16 = (blue16) / i;
	}

	//Amplify data differences
	if (red16 > 30)
	{
		red16 = red16 - 30;
	}

	if(green16 > 30)
	{
		green16 = green16 - 30;
	}

	if(blue16 > 30)
	{
		blue16 = blue16 - 30;
	}

	red16 = red16 * 255 / 225;
	green16 = green16 * 255 / 225;
	blue16 = blue16 * 255 / 225;

	if (red16 > 255)
	{
		red16 = 255;
	}
	if (green16 > 255)
	{
		green16 = 255;
	}
	if (blue16 > 255)
	{
		blue16 = 255;
	}

	*red = red16;
	*blue = blue16;
	*green = green16;
}
