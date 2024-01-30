#ifndef AUTO_SOLVER_H
#define AUTO_SOLVER_H

#include "./helper.h"

#define CHANGE_FACE_3_MOVES_DURATION 30000
#define CHANGE_FACE_2_MOVES_DURATION 20000
#define CHANGE_FACE_1_MOVE_DURATION 7000
#define READ_COLOR_WITH_TURNING 5000

int auto_rubik_solve();
void auto_color_setup();

#endif