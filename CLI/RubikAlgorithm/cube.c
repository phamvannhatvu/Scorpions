#include "cube.h"

// For STANDARD3X3 variation only
int initCube(struct CUBE* cube, enum VARIATION var) {
    if (cube == NULL) return 1;
    if (var != STANDARD3X3) return 1;
    cube->var = var;
    switch(cube->var) {
        case NOVARIATION:
            cube->coreNum = 0;
            cube->cornerNum = 0;
            cube->edgeNum = 0;
            cube->centerNum = 0;
            break;
        case STANDARD2X2:
            cube->coreNum = 0;
            cube->cornerNum = 8;
            cube->edgeNum = 0;
            cube->centerNum = 0;
            break;
        case STANDARD3X3:
            cube->coreNum = 1;
            cube->cornerNum = 8;
            cube->edgeNum = 12;
            cube->centerNum = 0;
            break;
        case STANDARD4X4:
            cube->coreNum = 0;
            cube->cornerNum = 8;
            cube->edgeNum = 24;
            cube->centerNum = 24;
            break;
        case STANDARD5X5:
            cube->coreNum = 1;
            cube->cornerNum = 8;
            cube->edgeNum = 36;
            cube->centerNum = 48;
            break;
        default:
            return 1;
    }
    cube->pieces = malloc((cube->coreNum + cube->cornerNum + cube->edgeNum + cube->centerNum) * sizeof(struct PIECE));
    int pindex = 0;
    for (pindex; pindex < cube->coreNum; pindex ++) {
        if (initPiece(cube->pieces + pindex, CORE)) return 1;
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum; pindex ++) {
        if (initPiece(cube->pieces + pindex, CORNER)) return 1;
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum + cube->edgeNum; pindex ++) {
        if (initPiece(cube->pieces + pindex, EDGE)) return 1;
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum + cube->edgeNum + cube->centerNum; pindex ++) {
        if (initPiece(cube->pieces + pindex, CENTER)) return 1;
    }
    ((cube->pieces + 0)->cells + 0)->side = UP;
    ((cube->pieces + 0)->cells + 1)->side = LEFT;
    ((cube->pieces + 0)->cells + 2)->side = FRONT;
    ((cube->pieces + 0)->cells + 3)->side = RIGHT;
    ((cube->pieces + 0)->cells + 4)->side = BACK;
    ((cube->pieces + 0)->cells + 5)->side = DOWN;
    ((cube->pieces + 1)->cells + 0)->side = UP;
    ((cube->pieces + 1)->cells + 1)->side = LEFT;
    ((cube->pieces + 1)->cells + 2)->side = FRONT;
    ((cube->pieces + 2)->cells + 0)->side = UP;
    ((cube->pieces + 2)->cells + 1)->side = FRONT;
    ((cube->pieces + 2)->cells + 2)->side = RIGHT;
    ((cube->pieces + 3)->cells + 0)->side = UP;
    ((cube->pieces + 3)->cells + 1)->side = RIGHT;
    ((cube->pieces + 3)->cells + 2)->side = BACK;
    ((cube->pieces + 4)->cells + 0)->side = UP;
    ((cube->pieces + 4)->cells + 1)->side = BACK;
    ((cube->pieces + 4)->cells + 2)->side = LEFT;
    ((cube->pieces + 5)->cells + 0)->side = DOWN;
    ((cube->pieces + 5)->cells + 1)->side = FRONT;
    ((cube->pieces + 5)->cells + 2)->side = LEFT;
    ((cube->pieces + 6)->cells + 0)->side = DOWN;
    ((cube->pieces + 6)->cells + 1)->side = RIGHT;
    ((cube->pieces + 6)->cells + 2)->side = FRONT;
    ((cube->pieces + 7)->cells + 0)->side = DOWN;
    ((cube->pieces + 7)->cells + 1)->side = BACK;
    ((cube->pieces + 7)->cells + 2)->side = RIGHT;
    ((cube->pieces + 8)->cells + 0)->side = DOWN;
    ((cube->pieces + 8)->cells + 1)->side = LEFT;
    ((cube->pieces + 8)->cells + 2)->side = BACK;
    ((cube->pieces + 9)->cells + 0)->side = UP;
    ((cube->pieces + 9)->cells + 1)->side = LEFT;
    ((cube->pieces + 10)->cells + 0)->side = UP;
    ((cube->pieces + 10)->cells + 1)->side = FRONT;
    ((cube->pieces + 11)->cells + 0)->side = UP;
    ((cube->pieces + 11)->cells + 1)->side = RIGHT;
    ((cube->pieces + 12)->cells + 0)->side = UP;
    ((cube->pieces + 12)->cells + 1)->side = BACK;
    ((cube->pieces + 13)->cells + 0)->side = LEFT;
    ((cube->pieces + 13)->cells + 1)->side = FRONT;
    ((cube->pieces + 14)->cells + 0)->side = RIGHT;
    ((cube->pieces + 14)->cells + 1)->side = FRONT;
    ((cube->pieces + 15)->cells + 0)->side = RIGHT;
    ((cube->pieces + 15)->cells + 1)->side = BACK;
    ((cube->pieces + 16)->cells + 0)->side = LEFT;
    ((cube->pieces + 16)->cells + 1)->side = BACK;
    ((cube->pieces + 17)->cells + 0)->side = DOWN;
    ((cube->pieces + 17)->cells + 1)->side = LEFT;
    ((cube->pieces + 18)->cells + 0)->side = DOWN;
    ((cube->pieces + 18)->cells + 1)->side = FRONT;
    ((cube->pieces + 19)->cells + 0)->side = DOWN;
    ((cube->pieces + 19)->cells + 1)->side = RIGHT;
    ((cube->pieces + 20)->cells + 0)->side = DOWN;
    ((cube->pieces + 20)->cells + 1)->side = BACK;
    return 0;
}

int destroyCube(struct CUBE* cube) {
    if (cube == NULL) return 1;
    for (int i = 0; i < cube->coreNum + cube->cornerNum + cube->edgeNum + cube->centerNum; i ++) {
        if (destroyPiece(cube->pieces + i)) return 1;
    }
    free(cube->pieces);
    cube->pieces = NULL;
    cube->coreNum = 0;
    cube->cornerNum = 0;
    cube->edgeNum = 0;
    cube->centerNum = 0;
    cube->var = NOVARIATION;
    return 0;
}

// For STANDARD3X3 variation only
int setCube(struct CUBE* cube, enum VARIATION var, enum COLOR* colors) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    if (colors == NULL) {
        int maxCell = cube->coreNum * 6 + cube->cornerNum * 3 + cube->edgeNum * 2 + cube->centerNum * 1;
        colors = malloc(maxCell * sizeof(enum COLOR));
        colors[15] = colors[36] = colors[12] = colors[30] = colors[0] = colors[34] = colors[6] = colors[32] = colors[9] = WHITE;
        colors[17] = colors[31] = colors[7] = colors[44] = colors[1] = colors[38] = colors[28] = colors[47] = colors[20] = ORANGE;
        colors[8] = colors[33] = colors[10] = colors[39] = colors[2] = colors[41] = colors[19] = colors[49] = colors[23] = GREEN;
        colors[11] = colors[35] = colors[13] = colors[40] = colors[3] = colors[42] = colors[22] = colors[51] = colors[26] = RED;
        colors[14] = colors[37] = colors[16] = colors[43] = colors[4] = colors[45] = colors[25] = colors[53] = colors[29] = BLUE;
        colors[18] = colors[48] = colors[21] = colors[46] = colors[5] = colors[50] = colors[27] = colors[52] = colors[24] = YELLOW;
        if (setCube(cube, var, colors)) return 1;
        free(colors);
        colors = NULL;
        return 0;
    }
    if (setPiece(cube->pieces + 0, CORE, colors + 0)) return 1;
    if (setPiece(cube->pieces + 1, CORNER, colors + 6)) return 1;
    if (setPiece(cube->pieces + 2, CORNER, colors + 9)) return 1;
    if (setPiece(cube->pieces + 3, CORNER, colors + 12)) return 1;
    if (setPiece(cube->pieces + 4, CORNER, colors + 15)) return 1;
    if (setPiece(cube->pieces + 5, CORNER, colors + 18)) return 1;
    if (setPiece(cube->pieces + 6, CORNER, colors + 21)) return 1;
    if (setPiece(cube->pieces + 7, CORNER, colors + 24)) return 1;
    if (setPiece(cube->pieces + 8, CORNER, colors + 27)) return 1;
    if (setPiece(cube->pieces + 9, EDGE, colors + 30)) return 1;
    if (setPiece(cube->pieces + 10, EDGE, colors + 32)) return 1;
    if (setPiece(cube->pieces + 11, EDGE, colors + 34)) return 1;
    if (setPiece(cube->pieces + 12, EDGE, colors + 36)) return 1;
    if (setPiece(cube->pieces + 13, EDGE, colors + 38)) return 1;
    if (setPiece(cube->pieces + 14, EDGE, colors + 40)) return 1;
    if (setPiece(cube->pieces + 15, EDGE, colors + 42)) return 1;
    if (setPiece(cube->pieces + 16, EDGE, colors + 44)) return 1;
    if (setPiece(cube->pieces + 17, EDGE, colors + 46)) return 1;
    if (setPiece(cube->pieces + 18, EDGE, colors + 48)) return 1;
    if (setPiece(cube->pieces + 19, EDGE, colors + 50)) return 1;
    if (setPiece(cube->pieces + 20, EDGE, colors + 52)) return 1;
    return 0;
}

// For STANDARD3X3 variation only
int printCube(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int maxCell = cube->coreNum * 6 + cube->cornerNum * 3 + cube->edgeNum * 2 + cube->centerNum * 1;
    char* colorCodes = malloc(maxCell * sizeof(char));
    int pindex = 0;
    int cindex = 0;
    for (pindex; pindex < cube->coreNum; pindex ++) {
        for (int i = 0; i < CORE; i ++, cindex ++) {
            if (getColorCode((cube->pieces + pindex)->cells + i, colorCodes + cindex)) return 1;
        }
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum; pindex ++) {
        for (int i = 0; i < CORNER; i ++, cindex ++) {
            if (getColorCode((cube->pieces + pindex)->cells + i, colorCodes + cindex)) return 1;
        }
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum + cube->edgeNum; pindex ++) {
        for (int i = 0; i < EDGE; i ++, cindex ++) {
            if (getColorCode((cube->pieces + pindex)->cells + i, colorCodes + cindex)) return 1;
        }
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum + cube->edgeNum + cube->centerNum; pindex ++) {
        for (int i = 0; i < CENTER; i ++, cindex ++) {
            if (getColorCode((cube->pieces + pindex)->cells + i, colorCodes + cindex)) return 1;
        }
    }
    printf("\n\t%c %c %c\n\t%c %c %c\n\t%c %c %c\n\n",
        colorCodes[15], colorCodes[36], colorCodes[12],
        colorCodes[30], colorCodes[0], colorCodes[34],
        colorCodes[6], colorCodes[32], colorCodes[9]);
    printf("%c %c %c\t%c %c %c\t%c %c %c\t%c %c %c\n",
        colorCodes[17], colorCodes[31], colorCodes[7],
        colorCodes[8], colorCodes[33], colorCodes[10],
        colorCodes[11], colorCodes[35], colorCodes[13],
        colorCodes[14], colorCodes[37], colorCodes[16]);
    printf("%c %c %c\t%c %c %c\t%c %c %c\t%c %c %c\n",
        colorCodes[44], colorCodes[1], colorCodes[38],
        colorCodes[39], colorCodes[2], colorCodes[41],
        colorCodes[40], colorCodes[3], colorCodes[42],
        colorCodes[43], colorCodes[4], colorCodes[45]);
    printf("%c %c %c\t%c %c %c\t%c %c %c\t%c %c %c\n",
        colorCodes[28], colorCodes[47], colorCodes[20],
        colorCodes[19], colorCodes[49], colorCodes[23],
        colorCodes[22], colorCodes[51], colorCodes[26],
        colorCodes[25], colorCodes[53], colorCodes[29]);
    printf("\n\t%c %c %c\n\t%c %c %c\n\t%c %c %c\n\n",
        colorCodes[18], colorCodes[48], colorCodes[21],
        colorCodes[46], colorCodes[5], colorCodes[50],
        colorCodes[27], colorCodes[52], colorCodes[24]);
    free(colorCodes);
    colorCodes = NULL;
    return 0;
}

// For STANDARD3X3 variation only
int printSide(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int maxCell = cube->coreNum * 6 + cube->cornerNum * 3 + cube->edgeNum * 2 + cube->centerNum * 1;
    int* sides = malloc(maxCell * sizeof(int));
    int pindex = 0;
    int cindex = 0;
    for (pindex; pindex < cube->coreNum; pindex ++) {
        for (int i = 0; i < CORE; i ++, cindex ++) {
            sides[cindex] = ((cube->pieces + pindex)->cells + i)->side;
        }
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum; pindex ++) {
        for (int i = 0; i < CORNER; i ++, cindex ++) {
            sides[cindex] = ((cube->pieces + pindex)->cells + i)->side;
        }
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum + cube->edgeNum; pindex ++) {
        for (int i = 0; i < EDGE; i ++, cindex ++) {
            sides[cindex] = ((cube->pieces + pindex)->cells + i)->side;
        }
    }
    for (pindex; pindex < cube->coreNum + cube->cornerNum + cube->edgeNum + cube->centerNum; pindex ++) {
        for (int i = 0; i < CENTER; i ++, cindex ++) {
            sides[cindex] = ((cube->pieces + pindex)->cells + i)->side;
        }
    }
    printf("\n\t%d %d %d\n\t%d %d %d\n\t%d %d %d\n\n",
        sides[15], sides[36], sides[12],
        sides[30], sides[0], sides[34],
        sides[6], sides[32], sides[9]);
    printf("%d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",
        sides[17], sides[31], sides[7],
        sides[8], sides[33], sides[10],
        sides[11], sides[35], sides[13],
        sides[14], sides[37], sides[16]);
    printf("%d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",
        sides[44], sides[1], sides[38],
        sides[39], sides[2], sides[41],
        sides[40], sides[3], sides[42],
        sides[43], sides[4], sides[45]);
    printf("%d %d %d\t%d %d %d\t%d %d %d\t%d %d %d\n",
        sides[28], sides[47], sides[20],
        sides[19], sides[49], sides[23],
        sides[22], sides[51], sides[26],
        sides[25], sides[53], sides[29]);
    printf("\n\t%d %d %d\n\t%d %d %d\n\t%d %d %d\n\n",
        sides[18], sides[48], sides[21],
        sides[46], sides[5], sides[50],
        sides[27], sides[52], sides[24]);
    free(sides);
    sides = NULL;
    return 0;
}