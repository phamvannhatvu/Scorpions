#ifndef _MOVE_H_
#define _MOVE_H_

#include <stdio.h>
#include <stdlib.h>
#include "cube.h"

#define PIECENUM 4

enum MOVE {
    NOMOVE,
    U, UI, U2, u, ui, u2,
    L, LI, L2, l, li, l2,
    F, FI, F2, f, fi, f2,
    R, RI, R2, r, ri, r2,
    B, BI, B2, b, bi, b2,
    D, DI, D2, d, di, d2
};

int movePiece(struct PIECE* piece, int times);
int movePieces(struct PIECE** pieces, int times);

int moveCube(struct CUBE* cube, enum MOVE move);
int moveCubes(struct CUBE* cube, int num, enum MOVE* moves);

int printMove(enum MOVE move);

#endif