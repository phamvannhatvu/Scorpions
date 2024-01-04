#include "move.h"

int movePiece(struct PIECE* piece, int times) {
    if (piece == NULL) return 1;
    if (piece->type < 2) return 1;
    struct CELL temp;
    if (initCell(&temp)) return 1;
    for (int i = 0; i < times % piece->type; i ++) {
        if (coppyCell(piece->cells + 0, &temp)) return 1;
        for (int j = 0; j < piece->type - 1; j ++) {
            if (coppyCell(piece->cells + j + 1, piece->cells + j)) return 1;
        }
        if (coppyCell(&temp, piece->cells + piece->type - 1)) return 1;
    }
    if (destroyCell(&temp)) return 1;
    return 0;
}

int movePieces(struct PIECE** pieces, int times) {
    if (pieces == NULL) return 1;
    for (int i = 0; i < PIECENUM; i ++) {
        if (pieces[i] == NULL) return 1;
    }
    for (int i = 1; i < PIECENUM; i ++) {
        if (pieces[i]->type != pieces[0]->type) return 1;
    }
    struct PIECE temp;
    if (initPiece(&temp, pieces[0]->type)) return 1;
    for (int i = 0; i < times % PIECENUM; i ++) {
        if (coppyPiece(pieces[0], &temp)) return 1;
        for (int j = 0; j < PIECENUM - 1; j ++) {
            if (coppyPiece(pieces[j + 1], pieces[j])) return 1;
        }
        if (coppyPiece(&temp, pieces[PIECENUM - 1])) return 1;
    }
    if (destroyPiece(&temp)) return 1;
    return 0;
}

// For STANDARD3X3 variation only
int moveCube(struct CUBE* cube, enum MOVE move) {
    if (cube == NULL) return 1;
    struct PIECE** pieces = malloc(PIECENUM * sizeof(struct PIECE*));
    switch (move) {
        case NOMOVE:
            break;
        case U:
            pieces[0] = cube->pieces + 1;
            pieces[1] = cube->pieces + 2;
            pieces[2] = cube->pieces + 3;
            pieces[3] = cube->pieces + 4;
            if (movePieces(pieces, 1)) return 1;
            pieces[0] = cube->pieces + 9;
            pieces[1] = cube->pieces + 10;
            pieces[2] = cube->pieces + 11;
            pieces[3] = cube->pieces + 12;
            if (movePieces(pieces, 1)) return 1;
            break;
        case UI:
            pieces[0] = cube->pieces + 4;
            pieces[1] = cube->pieces + 3;
            pieces[2] = cube->pieces + 2;
            pieces[3] = cube->pieces + 1;
            if (movePieces(pieces, 1)) return 1;
            pieces[0] = cube->pieces + 12;
            pieces[1] = cube->pieces + 11;
            pieces[2] = cube->pieces + 10;
            pieces[3] = cube->pieces + 9;
            if (movePieces(pieces, 1)) return 1;
            break;
        case U2:
            pieces[0] = cube->pieces + 1;
            pieces[1] = cube->pieces + 2;
            pieces[2] = cube->pieces + 3;
            pieces[3] = cube->pieces + 4;
            if (movePieces(pieces, 2)) return 1;
            pieces[0] = cube->pieces + 9;
            pieces[1] = cube->pieces + 10;
            pieces[2] = cube->pieces + 11;
            pieces[3] = cube->pieces + 12;
            if (movePieces(pieces, 2)) return 1;
            break;
        case L:
            pieces[0] = cube->pieces + 1;
            pieces[1] = cube->pieces + 4;
            pieces[2] = cube->pieces + 8;
            pieces[3] = cube->pieces + 5;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 2)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 2)) return 1;
            pieces[0] = cube->pieces + 16;
            pieces[1] = cube->pieces + 17;
            pieces[2] = cube->pieces + 13;
            pieces[3] = cube->pieces + 9;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            break;
        case LI:
            pieces[0] = cube->pieces + 5;
            pieces[1] = cube->pieces + 8;
            pieces[2] = cube->pieces + 4;
            pieces[3] = cube->pieces + 1;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 2)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 2)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            pieces[0] = cube->pieces + 9;
            pieces[1] = cube->pieces + 13;
            pieces[2] = cube->pieces + 17;
            pieces[3] = cube->pieces + 16;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            break;
        case L2:
            pieces[0] = cube->pieces + 1;
            pieces[1] = cube->pieces + 4;
            pieces[2] = cube->pieces + 8;
            pieces[3] = cube->pieces + 5;
            if (movePieces(pieces, 2)) return 1;
            pieces[0] = cube->pieces + 16;
            pieces[1] = cube->pieces + 17;
            pieces[2] = cube->pieces + 13;
            pieces[3] = cube->pieces + 9;
            if (movePieces(pieces, 2)) return 1;
            break;
        case F:
            pieces[0] = cube->pieces + 5;
            pieces[1] = cube->pieces + 6;
            pieces[2] = cube->pieces + 2;
            pieces[3] = cube->pieces + 1;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 2)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 2)) return 1;
            pieces[0] = cube->pieces + 13;
            pieces[1] = cube->pieces + 18;
            pieces[2] = cube->pieces + 14;
            pieces[3] = cube->pieces + 10;
            if (movePieces(pieces, 1)) return 1;
            break;
        case FI:
            pieces[0] = cube->pieces + 1;
            pieces[1] = cube->pieces + 2;
            pieces[2] = cube->pieces + 6;
            pieces[3] = cube->pieces + 5;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 2)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 2)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            pieces[0] = cube->pieces + 10;
            pieces[1] = cube->pieces + 14;
            pieces[2] = cube->pieces + 18;
            pieces[3] = cube->pieces + 13;
            if (movePieces(pieces, 1)) return 1;
            break;
        case F2:
            pieces[0] = cube->pieces + 5;
            pieces[1] = cube->pieces + 6;
            pieces[2] = cube->pieces + 2;
            pieces[3] = cube->pieces + 1;
            if (movePieces(pieces, 2)) return 1;
            pieces[0] = cube->pieces + 13;
            pieces[1] = cube->pieces + 18;
            pieces[2] = cube->pieces + 14;
            pieces[3] = cube->pieces + 10;
            if (movePieces(pieces, 2)) return 1;
            break;
        case R:
            pieces[0] = cube->pieces + 2;
            pieces[1] = cube->pieces + 6;
            pieces[2] = cube->pieces + 7;
            pieces[3] = cube->pieces + 3;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 2)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 2)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            pieces[0] = cube->pieces + 11;
            pieces[1] = cube->pieces + 14;
            pieces[2] = cube->pieces + 19;
            pieces[3] = cube->pieces + 15;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            break;
        case RI:
            pieces[0] = cube->pieces + 3;
            pieces[1] = cube->pieces + 7;
            pieces[2] = cube->pieces + 6;
            pieces[3] = cube->pieces + 2;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 2)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 2)) return 1;
            pieces[0] = cube->pieces + 15;
            pieces[1] = cube->pieces + 19;
            pieces[2] = cube->pieces + 14;
            pieces[3] = cube->pieces + 11;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            break;
        case R2:
            pieces[0] = cube->pieces + 2;
            pieces[1] = cube->pieces + 6;
            pieces[2] = cube->pieces + 7;
            pieces[3] = cube->pieces + 3;
            if (movePieces(pieces, 2)) return 1;
            pieces[0] = cube->pieces + 11;
            pieces[1] = cube->pieces + 14;
            pieces[2] = cube->pieces + 19;
            pieces[3] = cube->pieces + 15;
            if (movePieces(pieces, 2)) return 1;
            break;
        case B:
            pieces[0] = cube->pieces + 7;
            pieces[1] = cube->pieces + 8;
            pieces[2] = cube->pieces + 4;
            pieces[3] = cube->pieces + 3;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 1)) return 1;
            if (movePiece(pieces[1], 2)) return 1;
            if (movePiece(pieces[2], 1)) return 1;
            if (movePiece(pieces[3], 2)) return 1;
            pieces[0] = cube->pieces + 15;
            pieces[1] = cube->pieces + 20;
            pieces[2] = cube->pieces + 16;
            pieces[3] = cube->pieces + 12;
            if (movePieces(pieces, 1)) return 1;
            break;
        case BI:
            pieces[0] = cube->pieces + 3;
            pieces[1] = cube->pieces + 4;
            pieces[2] = cube->pieces + 8;
            pieces[3] = cube->pieces + 7;
            if (movePieces(pieces, 1)) return 1;
            if (movePiece(pieces[0], 2)) return 1;
            if (movePiece(pieces[1], 1)) return 1;
            if (movePiece(pieces[2], 2)) return 1;
            if (movePiece(pieces[3], 1)) return 1;
            pieces[0] = cube->pieces + 12;
            pieces[1] = cube->pieces + 16;
            pieces[2] = cube->pieces + 20;
            pieces[3] = cube->pieces + 15;
            if (movePieces(pieces, 1)) return 1;
            break;
        case B2:
            pieces[0] = cube->pieces + 7;
            pieces[1] = cube->pieces + 8;
            pieces[2] = cube->pieces + 4;
            pieces[3] = cube->pieces + 3;
            if (movePieces(pieces, 2)) return 1;
            pieces[0] = cube->pieces + 15;
            pieces[1] = cube->pieces + 20;
            pieces[2] = cube->pieces + 16;
            pieces[3] = cube->pieces + 12;
            if (movePieces(pieces, 2)) return 1;
            break;
        case D:
            pieces[0] = cube->pieces + 8;
            pieces[1] = cube->pieces + 7;
            pieces[2] = cube->pieces + 6;
            pieces[3] = cube->pieces + 5;
            if (movePieces(pieces, 1)) return 1;
            pieces[0] = cube->pieces + 20;
            pieces[1] = cube->pieces + 19;
            pieces[2] = cube->pieces + 18;
            pieces[3] = cube->pieces + 17;
            if (movePieces(pieces, 1)) return 1;
            break;
        case DI:
            pieces[0] = cube->pieces + 5;
            pieces[1] = cube->pieces + 6;
            pieces[2] = cube->pieces + 7;
            pieces[3] = cube->pieces + 8;
            if (movePieces(pieces, 1)) return 1;
            pieces[0] = cube->pieces + 17;
            pieces[1] = cube->pieces + 18;
            pieces[2] = cube->pieces + 19;
            pieces[3] = cube->pieces + 20;
            if (movePieces(pieces, 1)) return 1;
            break;
        case D2:
            pieces[0] = cube->pieces + 8;
            pieces[1] = cube->pieces + 7;
            pieces[2] = cube->pieces + 6;
            pieces[3] = cube->pieces + 5;
            if (movePieces(pieces, 2)) return 1;
            pieces[0] = cube->pieces + 20;
            pieces[1] = cube->pieces + 19;
            pieces[2] = cube->pieces + 18;
            pieces[3] = cube->pieces + 17;
            if (movePieces(pieces, 2)) return 1;
            break;
        default:
            return 1;
    }
    free(pieces);
    pieces = NULL;
    return 0;
}

int moveCubes(struct CUBE* cube, int num, enum MOVE* moves) {
    if (cube == NULL || num < 0 || moves == NULL) return 1;
    printf("Moves: ");
    for (int i = 0; i < num; i ++) {
        if (moveCube(cube, moves[i])) return 1;
        if (printMove(moves[i])) return 1;
    }
    printf("\n");
    return 0;
}

int printMove(enum MOVE move) {
    switch (move) {
        case NOMOVE:
            break;
        case U:
            printf("U ");
            break;
        case UI:
            printf("U' ");
            break;
        case U2:
            printf("U2 ");
            break;
        case u:
            printf("u ");
            break;
        case ui:
            printf("u' ");
            break;
        case u2:
            printf("u2 ");
            break;
        case L:
            printf("L ");
            break;
        case LI:
            printf("L' ");
            break;
        case L2:
            printf("L2 ");
            break;
        case l:
            printf("l ");
            break;
        case li:
            printf("l' ");
            break;
        case l2:
            printf("l2 ");
            break;
        case F:
            printf("F ");
            break;
        case FI:
            printf("F' ");
            break;
        case F2:
            printf("F2 ");
            break;
        case f:
            printf("f ");
            break;
        case fi:
            printf("f' ");
            break;
        case f2:
            printf("f2 ");
            break;
        case R:
            printf("R ");
            break;
        case RI:
            printf("R' ");
            break;
        case R2:
            printf("R2 ");
            break;
        case r:
            printf("r ");
            break;
        case ri:
            printf("r' ");
            break;
        case r2:
            printf("r2 ");
            break;
        case B:
            printf("B ");
            break;
        case BI:
            printf("B' ");
            break;
        case B2:
            printf("B2 ");
            break;
        case b:
            printf("b ");
            break;
        case bi:
            printf("b' ");
            break;
        case b2:
            printf("b2 ");
            break;
        case D:
            printf("D ");
            break;
        case DI:
            printf("D' ");
            break;
        case D2:
            printf("D2 ");
            break;
        case d:
            printf("d ");
            break;
        case di:
            printf("d' ");
            break;
        case d2:
            printf("d2 ");
            break;
        default:
            return 1;
    }
    return 0;
}