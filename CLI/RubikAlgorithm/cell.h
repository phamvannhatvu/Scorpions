#ifndef _CELL_H_
#define _CELL_H_

#include <stdio.h>
#include <stdlib.h>

enum COLOR {
    NOCOLOR,
    WHITE,
    ORANGE,
    GREEN,
    RED,
    BLUE,
    YELLOW
};

enum SIDE {
    NOSIDE,
    UP,
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    DOWN
};

struct CELL {
    enum COLOR color;
    enum SIDE side;
};

// Standard functions of struct CELL
int initCell(struct CELL* cell);
int destroyCell(struct CELL* cell);
int setCell(struct CELL* cell, enum COLOR color);

// Operators of struct CELL
int coppyCell(struct CELL* source, struct CELL* destination);
int compareCell(struct CELL* cell1, struct CELL* cell2, int* result);

// Support functions
int getColor(struct CELL* cell, enum COLOR* color);
int getColorCode(struct CELL* cell, char* color);

#endif