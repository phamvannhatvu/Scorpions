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


#include "color_sensor.h"
#include "usbd_cdc_if.h"

void read_i2c_word(uint8_t reg_addr, uint8_t *data)
{
	HAL_I2C_Mem_Read(&hi2c2, SENSOR_ADDR, COMMAND_BIT | READ_WORD | reg_addr, I2C_MEMADD_SIZE_8BIT, data, 2, 1000);
}

void read_i2c_byte(uint8_t reg_addr, uint8_t *data)
{
	HAL_I2C_Mem_Read(&hi2c2, SENSOR_ADDR, COMMAND_BIT | reg_addr, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
}

void write_i2c_byte(uint8_t reg_addr, uint8_t *data)
{
	HAL_I2C_Mem_Write(&hi2c2, SENSOR_ADDR, COMMAND_BIT | reg_addr, I2C_MEMADD_SIZE_8BIT, data, 1, 1000);
}

void color_sensor_init()
{
	uint8_t en[1] = {0xB};
	write_i2c_byte(EN_ADDR, en);
	HAL_Delay(3);
}

void read_rgb(uint8_t *red, uint8_t *green, uint8_t *blue)
{
	uint8_t reds[2] = {0x00, 0x00};
	uint8_t greens[2] = {0x00, 0x00};
	uint8_t blues[2] = {0x00, 0x00};

	read_i2c_word(RDATAL, reds);
	read_i2c_word(GDATAL, greens);
	read_i2c_word(BDATAL, blues);
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
