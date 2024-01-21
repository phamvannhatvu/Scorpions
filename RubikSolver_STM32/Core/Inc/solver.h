/*
 * solver.h
 *
 *  Created on: Jan 5, 2024
 *      Author: ADMIN
 */

#ifndef INC_SOLVER_H_
#define INC_SOLVER_H_

#include "global.h"
#include "usbd_cdc_if.h"
#include "color_reading.h"
#include "helper.h"
#include "robot.h"

void manualColorSetup();
void manualRubikSolve();
void autoColorSetup();
void autoRubikSolve();

#endif /* INC_SOLVER_H_ */
