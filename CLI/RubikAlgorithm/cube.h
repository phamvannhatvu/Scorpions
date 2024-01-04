#ifndef _CUBE_H_
#define _CUBE_H_

#include <stdio.h>
#include <stdlib.h>
#include "piece.h"

enum VARIATION {
    NOVARIATION,
    STANDARD2X2,
    STANDARD3X3,
    STANDARD4X4,
    STANDARD5X5
};

struct CUBE {
    enum VARIATION var;
    int coreNum;
    int cornerNum;
    int edgeNum;
    int centerNum;
    struct PIECE* pieces;
};

// Standard functions of struct CUBE
int initCube(struct CUBE* cube, enum VARIATION var);
int destroyCube(struct CUBE* cube);
int setCube(struct CUBE* cube, enum VARIATION var, enum COLOR* colors);

// Support functions
int printCube(struct CUBE* cube);
int printSide(struct CUBE* cube);

#endif