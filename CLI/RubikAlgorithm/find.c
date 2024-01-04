#include "find.h"

int findCell(struct PIECE* piece, enum COLOR color, int* result, int* index) {
    if (piece == NULL || result == NULL || index == NULL) return 1;
    struct CELL temp;
    if (initCell(&temp)) return 1;
    if (setCell(&temp, color)) return 1;
    int cindex = 0;
    int flag = 0;
    for (cindex = 0; cindex < piece->type; cindex ++) {
        if (compareCell(piece->cells + cindex, &temp, &flag)) return 1;
        if (flag == 1) break;
    }
    if (flag == 0) {
        *result = 0;
        return 0;
    }
    *index = cindex;
    *result = 1;
    return 0;
}

// For STANDARD3X3 variation only
int findPiece(struct CUBE* cube, enum TYPE type, enum COLOR* colors, int* result, int* index, enum SIDE* side) {
    if (cube == NULL || type < 0 || colors == NULL || index == NULL || side == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int startIndex = 0;
    int endIndex = 0;
    switch (type) {
        case CORE:
            startIndex = 0;
            endIndex = cube->coreNum;
            break;
        case CORNER:
            startIndex = cube->coreNum;
            endIndex = cube->coreNum + cube->cornerNum;
            break;
        case EDGE:
            startIndex = cube->coreNum + cube->cornerNum;
            endIndex = cube->coreNum + cube->cornerNum + cube->edgeNum;
            break;
        case CENTER:
            startIndex = cube->coreNum + cube->cornerNum + cube->edgeNum;
            endIndex = cube->coreNum + cube->cornerNum + cube->edgeNum + cube->centerNum;
            break;
        default:
            return 1;
    }
    struct PIECE temp;
    if (initPiece(&temp, type)) return 1;
    if (setPiece(&temp, type, colors)) return 1;
    int pindex = 0;
    int flag = 0;
    for (pindex = startIndex; pindex < endIndex; pindex ++) {
        if (comparePiece(cube->pieces + pindex, &temp, &flag)) return 1;
        if (flag == 1) break;
    }
    if (flag == 0) {
        *result = 0;
        return 0;
    }
    *index = pindex;
    int cindex = 0;
    if (findCell(cube->pieces + pindex, colors[0], &flag, &cindex)) return 1;
    if (flag == 0) {
        *result = 0;
        return 0;
    }
    *side = ((cube->pieces + pindex)->cells + cindex)->side;
    *result = 1;
    return 0;
}