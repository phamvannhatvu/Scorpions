/*
 * helper.c
 *
 *  Created on: Sep 15, 2023
 *      Author: ADMIN
 */

#include "helper.h"
#include "usbd_cdc_if.h"

int data_equal(uint8_t *data, uint8_t len, char *literal)
{
	if (len != strlen(literal)) return 0;
	for (uint8_t i = 0; i < len; ++i)
	{
		if (data[i] != literal[i]) return 0;
	}
	return 1;
}


