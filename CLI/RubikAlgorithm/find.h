#ifndef _FIND_H_
#define _FIND_H_

#include <stdio.h>
#include <stdlib.h>
#include "cube.h"

int findCell(struct PIECE* piece, enum COLOR color, int* result, int* index);
int findPiece(struct CUBE* cube, enum TYPE type, enum COLOR* colors, int* result, int* index, enum SIDE* side);

#endif