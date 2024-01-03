#include "cfop.h"

int convertPieceIndexs(int times, int num, int* indexs, int* reIndexs) {
    if (times < 0 || times > CFOPTIMES || num < 0 || indexs == NULL || reIndexs == NULL) return 1;
    for (int i = 0; i < num; i ++) {
        int flag = 0;
        for (int j = 0; j < CFOPPIECE; j ++) {
            if (indexs[i] == INDEXS[times][j]) {
                reIndexs[i] = INDEXS[0][j];
                flag = 1;
                break;
            }
        }
        if (flag == 0) return 1;
    }
    return 0;
}

int convertPieceSides(int times, int num, enum SIDE* sides, enum SIDE* reSides) {
    if (times < 0 || times > CFOPTIMES || num < 0 || sides == NULL || reSides == NULL) return 1;
    for (int i = 0; i < num; i ++) {
        int flag = 0;
        for (int j = 0; j < CFOPSIDE; j ++) {
            if (sides[i] == SIDES[times][j]) {
                reSides[i] = SIDES[0][j];
                flag = 1;
                break;
            }
        }
        if (flag == 0) return 1;
    }
    return 0;
}

int convertUpCells(int times, int num, int* indexs, int* reIndexs) {
    if (times < 0 || times > CFOPTIMES || num < 0 || indexs == NULL || reIndexs == NULL) return 1;
    for (int i = 0; i < num; i ++) {
        reIndexs[i] = indexs[(i + times) % num];
    }
    return 0;
}

int convertUpPieces(int times, int num, int* indexs, int* reIndexs) {
    if (times < 0 || times > CFOPTIMES || num < 0 || indexs == NULL || reIndexs == NULL) return 1;
    for (int i = 0; i < num; i ++) {
        reIndexs[i] = indexs[(i + times) % num];
    }
    return 0;
}

int revertMoves(int times, int num, enum MOVE* moves, enum MOVE* reMoves) {
    if (times < 0 || times > CFOPTIMES || num < 0 || moves == NULL || reMoves == NULL) return 1;
    for (int i = 0; i < num; i ++) {
        int flag = 0;
        for (int j = 0; j < CFOPMOVE; j ++) {
            if (moves[i] == MOVES[0][j]) {
                reMoves[i] = MOVES[times][j];
                flag = 1;
                break;
            }
        }
        if (flag == 0) return 1;
    }
    return 0;
}

int getCrossCode(int* indexs, enum SIDE* sides, char* code) {
    if (indexs == NULL || sides == NULL || code == NULL) return 1;
    sprintf(code, "%02d%01d", indexs[0], sides[0]);
    return 0;
}

int getF1LCode(int* indexs, enum SIDE* sides, char* code) {
    if (indexs == NULL || sides == NULL || code == NULL) return 1;
    sprintf(code, "%02d%01d", indexs[0], sides[0]);
    return 0;
}

int getF2LCode(int* indexs, enum SIDE* sides, char* code) {
    if (indexs == NULL || sides == NULL || code == NULL) return 1;
    sprintf(code, "%02d%01d", indexs[0], sides[0]);
    return 0;
}

int getOLLCode(int* cornerIndex, int* edgeIndex, char* code) {
    if (cornerIndex == NULL || edgeIndex == NULL || code == NULL) return 1;
    sprintf(code, "%01d%01d%01d%01d%01d%01d%01d%01d", cornerIndex[0], cornerIndex[1], cornerIndex[2], cornerIndex[3], edgeIndex[0], edgeIndex[1], edgeIndex[2], edgeIndex[3]);
    return 0;
}

int getPLLCode(int* cornerIndex, int* edgeIndex, char* code) {
    if (cornerIndex == NULL || edgeIndex == NULL || code == NULL) return 1;
    sprintf(code, "%02d%02d%02d%02d%02d%02d%02d%02d", cornerIndex[0], cornerIndex[1], cornerIndex[2], cornerIndex[3], edgeIndex[0], edgeIndex[1], edgeIndex[2], edgeIndex[3]);
    return 0;
}

int cfopSolve(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    if (getColor((cube->pieces + 0)->cells + 0, &UPCOLOR)) return 1;
    if (getColor((cube->pieces + 0)->cells + 1, &LEFTCOLOR)) return 1;
    if (getColor((cube->pieces + 0)->cells + 2, &FRONTCOLOR)) return 1;
    if (getColor((cube->pieces + 0)->cells + 3, &RIGHTCOLOR)) return 1;
    if (getColor((cube->pieces + 0)->cells + 4, &BACKCOLOR)) return 1;
    if (getColor((cube->pieces + 0)->cells + 5, &DOWNCOLOR)) return 1;
    printf("\nCFOP CROSS\n");
    if (cfopCross(cube)) return 1;
    printf("\nCFOP F1L\n");
    if (cfopF1L(cube)) return 1;
    printf("\nCFOP F2L\n");
    if (cfopF2L(cube)) return 1;
    printf("\nCFOP OLL\n");
    if (cfopOLL(cube)) return 1;
    printf("\nCFOP PLL\n");
    if (cfopPLL(cube)) return 1;
    return 0;
}

int cfopCross(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int flag = 0;
    int* index = malloc(sizeof(int));
    enum SIDE* side = malloc(sizeof(enum SIDE));
    enum COLOR colors[CFOPTIMES][EDGE] = {
        {DOWNCOLOR, LEFTCOLOR},
        {DOWNCOLOR, FRONTCOLOR},
        {DOWNCOLOR, RIGHTCOLOR},
        {DOWNCOLOR, BACKCOLOR}
    };
    for (int i = 0; i < CFOPTIMES; i ++) {
        if (findPiece(cube, EDGE, colors[i], &flag, index, side)) return 1;
        if (flag == 0) return 1;
        int* reIndex = malloc(sizeof(int));
        enum SIDE* reSide = malloc(sizeof(enum SIDE));
        char* code = malloc(CFOPCROSSCODE * sizeof(char));
        if (convertPieceIndexs(i, 1, index, reIndex)) return 1;
        if (convertPieceSides(i, 1, side, reSide)) return 1;
        if (getCrossCode(reIndex, reSide, code)) return 1;
        enum MOVE* moves = NULL;
        int count = 0;
        flag = 0;
        for (int j = 0; j < CFOPCROSSES; j ++) {
            if (strcmp(code, CROSSCODES[j]) == 0) {
                moves = CROSSSOLVE[j];
                count = CROSSSIZE[j];
                flag = 1;
                break;
            }
        }
        if (flag == 0) return 1;
        enum MOVE* reMoves = malloc(count * sizeof(enum MOVE));
        if (revertMoves(i, count, moves, reMoves)) return 1;
        if (moveCubes(cube, count, reMoves)) return 1;
        free(reIndex);
        reIndex = NULL;
        free(reSide);
        reSide = NULL;
        free(code);
        code = NULL;
        free(reMoves);
        reMoves = NULL;
    }
    free(index);
    index = NULL;
    free(side);
    side = NULL;
    return 0;
}

int cfopF1L(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int flag = 0;
    int* index = malloc(sizeof(int));
    enum SIDE* side = malloc(sizeof(enum SIDE));
    enum COLOR colors[CFOPTIMES][CORNER] = {
        {DOWNCOLOR, FRONTCOLOR, LEFTCOLOR},
        {DOWNCOLOR, RIGHTCOLOR, FRONTCOLOR},
        {DOWNCOLOR, BACKCOLOR, RIGHTCOLOR},
        {DOWNCOLOR, LEFTCOLOR, BACKCOLOR}
    };
    for (int i = 0; i < CFOPTIMES; i ++) {
        if (findPiece(cube, CORNER, colors[i], &flag, index, side)) return 1;
        if (flag == 0) return 1;
        int* reIndex = malloc(sizeof(int));
        enum SIDE* reSide = malloc(sizeof(enum SIDE));
        char* code = malloc(CFOPF1LCODE * sizeof(char));
        if (convertPieceIndexs(i, 1, index, reIndex)) return 1;
        if (convertPieceSides(i, 1, side, reSide)) return 1;
        if (getF1LCode(reIndex, reSide, code)) return 1;
        enum MOVE* moves = NULL;
        int count = 0;
        flag = 0;
        for (int j = 0; j < CFOPF1LS; j ++) {
            if (strcmp(code, F1LCODES[j]) == 0) {
                moves = F1LSOLVE[j];
                count = F1LSIZE[j];
                flag = 1;
                break;
            }
        }
        if (flag == 0) return 1;
        enum MOVE* reMoves = malloc(count * sizeof(enum MOVE));
        if (revertMoves(i, count, moves, reMoves)) return 1;
        if (moveCubes(cube, count, reMoves)) return 1;
        free(reIndex);
        reIndex = NULL;
        free(reSide);
        reSide = NULL;
        free(code);
        code = NULL;
        free(reMoves);
        reMoves = NULL;
    }
    free(index);
    index = NULL;
    free(side);
    side = NULL;
    return 0;
}

int cfopF2L(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int flag = 0;
    int* index = malloc(sizeof(int));
    enum SIDE* side = malloc(sizeof(enum SIDE));
    enum COLOR colors[CFOPTIMES][EDGE] = {
        {LEFTCOLOR, FRONTCOLOR},
        {FRONTCOLOR, RIGHTCOLOR},
        {RIGHTCOLOR, BACKCOLOR},
        {BACKCOLOR, LEFTCOLOR}
    };
    for (int i = 0; i < CFOPTIMES; i ++) {
        if (findPiece(cube, EDGE, colors[i], &flag, index, side)) return 1;
        if (flag == 0) return 1;
        int* reIndex = malloc(sizeof(int));
        enum SIDE* reSide = malloc(sizeof(enum SIDE));
        char* code = malloc(CFOPF2LCODE * sizeof(char));
        if (convertPieceIndexs(i, 1, index, reIndex)) return 1;
        if (convertPieceSides(i, 1, side, reSide)) return 1;
        if (getF2LCode(reIndex, reSide, code)) return 1;
        enum MOVE* moves = NULL;
        int count = 0;
        flag = 0;
        for (int j = 0; j < CFOPF2LS; j ++) {
            if (strcmp(code, F2LCODES[j]) == 0) {
                moves = F2LSOLVE[j];
                count = F2LSIZE[j];
                flag = 1;
                break;
            }
        }
        if (flag == 0) return 1;
        enum MOVE* reMoves = malloc(count * sizeof(enum MOVE));
        if (revertMoves(i, count, moves, reMoves)) return 1;
        if (moveCubes(cube, count, reMoves)) return 1;
        free(reIndex);
        reIndex = NULL;
        free(reSide);
        reSide = NULL;
        free(code);
        code = NULL;
        free(reMoves);
        reMoves = NULL;
    }
    free(index);
    index = NULL;
    free(side);
    side = NULL;
    return 0;
}

int cfopOLL(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int flag = 0;
    int* cornerIndexs = malloc(CFOPTIMES * sizeof(int));
    int* edgeIndexs = malloc(CFOPTIMES * sizeof(int));
    for (int i = 0; i < CFOPTIMES; i ++) {
        if (findCell(cube->pieces + cube->coreNum + i, UPCOLOR, &flag, cornerIndexs + i)) return 1;
        if (flag == 0) return 1;
    }
    for (int i = 0; i < CFOPTIMES; i ++) {
        if (findCell(cube->pieces + cube->coreNum + cube->cornerNum + i, UPCOLOR, &flag, edgeIndexs + i)) return 1;
        if (flag == 0) return 1;
    }
    enum MOVE* moves = NULL;
    int count = 0;
    int times = 0;
    flag = 0;
    for (int i = 0; i < CFOPTIMES; i ++) {
        int* cornerReIndexs = malloc(CFOPTIMES * sizeof(int));
        int* edgeReIndexs = malloc(CFOPTIMES * sizeof(int));
        char* code = malloc(CFOPOLLCODE * sizeof(char));
        if (convertUpCells(i, CFOPTIMES, cornerIndexs, cornerReIndexs)) return 1;
        if (convertUpCells(i, CFOPTIMES, edgeIndexs, edgeReIndexs)) return 1;
        if (getOLLCode(cornerReIndexs, edgeReIndexs, code)) return 1;
        for (int j = 0; j < CFOPOLLS; j ++) {
            if (strcmp(code, OLLCODES[j]) == 0) {
                moves = OLLSOLVE[j];
                count = OLLSIZE[j];
                times = i;
                flag = 1;
                break;
            }
        }
        free(cornerReIndexs);
        cornerReIndexs = NULL;
        free(edgeReIndexs);
        edgeReIndexs = NULL;
        free(code);
        code = NULL;
        if (flag == 1) break;
    }
    if (flag == 0) return 1;
    enum MOVE* reMoves = malloc(count * sizeof(enum MOVE));
    if (revertMoves(times, count, moves, reMoves)) return 1;
    if (moveCubes(cube, count, reMoves)) return 1;
    free(cornerIndexs);
    cornerIndexs = NULL;
    free(edgeIndexs);
    edgeIndexs = NULL;
    free(reMoves);
    reMoves = NULL;
    return 0;
}

int cfopPLL(struct CUBE* cube) {
    if (cube == NULL) return 1;
    if (cube->var != STANDARD3X3) return 1;
    int flag = 0;
    int* cornerIndexs = malloc(CFOPTIMES * sizeof(int));
    int* edgeIndexs = malloc(CFOPTIMES * sizeof(int));
    enum SIDE* cornerSides = malloc(CFOPTIMES * sizeof(enum SIDE));
    enum SIDE* edgeSides = malloc(CFOPTIMES * sizeof(enum SIDE));
    enum COLOR cornerColors[CFOPTIMES][CORNER] = {
        {UPCOLOR, LEFTCOLOR, FRONTCOLOR},
        {UPCOLOR, FRONTCOLOR, RIGHTCOLOR},
        {UPCOLOR, RIGHTCOLOR, BACKCOLOR},
        {UPCOLOR, BACKCOLOR, LEFTCOLOR}
    };
    enum COLOR edgeColors[CFOPTIMES][EDGE] = {
        {UPCOLOR, LEFTCOLOR},
        {UPCOLOR, FRONTCOLOR},
        {UPCOLOR, RIGHTCOLOR},
        {UPCOLOR, BACKCOLOR}
    };
    for (int i = 0; i < CFOPTIMES; i ++) {
        if (findPiece(cube, CORNER, cornerColors[i], &flag, cornerIndexs + i, cornerSides + i)) return 1;
        if (flag == 0) return 1;
    }
    for (int i = 0; i < CFOPTIMES; i ++) {
        if (findPiece(cube, EDGE, edgeColors[i], &flag, edgeIndexs + i, edgeSides + i)) return 1;
        if (flag == 0) return 1;
    }
    enum MOVE* moves = NULL;
    int count = 0;
    int times1st = 0;
    int times2nd = 0;
    flag = 0;
    for (int i = 0; i < CFOPTIMES; i ++) {
        int* corner1stReIndexs = malloc(CFOPTIMES * sizeof(int));
        int* edge1stReIndexs = malloc(CFOPTIMES * sizeof(int));
        enum SIDE* corner1stReSides = malloc(CFOPTIMES * sizeof(enum SIDE));
        enum SIDE* edge1stReSides = malloc(CFOPTIMES * sizeof(enum SIDE));
        if (convertPieceIndexs(i, CFOPTIMES, cornerIndexs, corner1stReIndexs)) return 1;
        if (convertPieceIndexs(i, CFOPTIMES, edgeIndexs, edge1stReIndexs)) return 1;
        if (convertPieceSides(i, CFOPTIMES, cornerSides, corner1stReSides)) return 1;
        if (convertPieceSides(i, CFOPTIMES, edgeSides, edge1stReSides)) return 1;
        for (int j = 0; j < CFOPTIMES; j ++) {
            int* corner2stReIndexs = malloc(CFOPTIMES * sizeof(int));
            int* edge2stReIndexs = malloc(CFOPTIMES * sizeof(int));
            if (convertUpPieces(j, CFOPTIMES, corner1stReIndexs, corner2stReIndexs)) return 1;
            if (convertUpPieces(j, CFOPTIMES, edge1stReIndexs, edge2stReIndexs)) return 1;
            char* code = malloc(CFOPPLLCODE * sizeof(char));
            getPLLCode(corner2stReIndexs, edge2stReIndexs, code);
            for (int k = 0; k < CFOPPLLS; k ++) {
                if (strcmp(code, PLLCODES[k]) == 0) {
                    moves = PLLSOLVE[k];
                    count = PLLSIZE[k];
                    times1st = i;
                    times2nd = j;
                    flag = 1;
                    break;
                }
            }
            free(corner2stReIndexs);
            corner2stReIndexs = NULL;
            free(edge2stReIndexs);
            edge2stReIndexs = NULL;
            free(code);
            code = NULL;
            if (flag == 1) break;
        }
        free(corner1stReIndexs);
        corner1stReIndexs = NULL;
        free(edge1stReIndexs);
        edge1stReIndexs = NULL;
        free(corner1stReSides);
        corner1stReSides = NULL;
        free(edge1stReSides);
        edge1stReSides = NULL;
        if (flag == 1) break;
    }
    if (flag == 0) return 1;
    flag = 0;
    int times = (times2nd - times1st + CFOPTIMES) % CFOPTIMES;
    enum MOVE* reMoves = malloc((count + 1) * sizeof(enum MOVE));
    if (revertMoves(times1st, count, moves, reMoves)) return 1;
    if (times != 0) {
        switch (reMoves[count - 1]) {
            case U:
                times = (times - 1 + CFOPTIMES) % CFOPTIMES;
                flag = 1;
                break;
            case UI:
                times = (times + 1 + CFOPTIMES) % CFOPTIMES;
                flag = 1;
                break;
            case U2:
                times = (times + 2 + CFOPTIMES) % CFOPTIMES;
                flag = 1;
                break;
            default:
                break;
        }
        enum MOVE lastMove = NOMOVE;
        switch (times) {
            case 0:
                break;
            case 1:
                lastMove = UI;
                break;
            case 2:
                lastMove = U2;
                break;
            case 3:
                lastMove = U;
                break;
            default:
                return 1;
        }
        if (flag == 0) {
            reMoves[count] = lastMove;
            count ++;
        }
        else {
            reMoves[count - 1] = lastMove;
            if (lastMove == NOMOVE) count --;
        }
    }
    if (moveCubes(cube, count, reMoves)) return 1;
    free(cornerIndexs);
    cornerIndexs = NULL;
    free(edgeIndexs);
    edgeIndexs = NULL;
    free(cornerSides);
    cornerSides = NULL;
    free(edgeSides);
    edgeSides = NULL;
    free(reMoves);
    reMoves = NULL;
    return 0;
}