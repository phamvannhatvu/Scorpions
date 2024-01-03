#ifndef _PIECE_H_
#define _PIECE_H_

#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

enum TYPE {
    NOTYPE,
    CENTER = 1,
    EDGE = 2,
    CORNER = 3,
    CORE = 6
};

struct PIECE {
    enum TYPE type;
    struct CELL* cells;
};

// Standard functions of struct PIECE
int initPiece(struct PIECE* piece, enum TYPE type);
int destroyPiece(struct PIECE* piece);
int setPiece(struct PIECE* piece, enum TYPE type, enum COLOR* colors);

// Operators of struct PIECE
int coppyPiece(struct PIECE* source, struct PIECE* destination);
int comparePiece(struct PIECE* piece1, struct PIECE* piece2, int* result);

#endif