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
    FILE* outputPtr = fopen("output.txt", "a");
    switch (move) {
        case NOMOVE:
            break;
        case U:
            fprintf(outputPtr, "z R z' ");
            break;
        case UI:
            fprintf(outputPtr, "z R' z' ");
            break;
        case U2:
            fprintf(outputPtr, "z R R z' ");
            break;
        case u:
            fprintf(outputPtr, "u ");
            break;
        case ui:
            fprintf(outputPtr, "u' ");
            break;
        case u2:
            fprintf(outputPtr, "u2 ");
            break;
        case L:
            fprintf(outputPtr, "L ");
            break;
        case LI:
            fprintf(outputPtr, "L' ");
            break;
        case L2:
            fprintf(outputPtr, "L L ");
            break;
        case l:
            fprintf(outputPtr, "l ");
            break;
        case li:
            fprintf(outputPtr, "l' ");
            break;
        case l2:
            fprintf(outputPtr, "l2 ");
            break;
        case F:
            fprintf(outputPtr, "F ");
            break;
        case FI:
            fprintf(outputPtr, "F' ");
            break;
        case F2:
            fprintf(outputPtr, "F F ");
            break;
        case f:
            fprintf(outputPtr, "f ");
            break;
        case fi:
            fprintf(outputPtr, "f' ");
            break;
        case f2:
            fprintf(outputPtr, "f2 ");
            break;
        case R:
            fprintf(outputPtr, "R ");
            break;
        case RI:
            fprintf(outputPtr, "R' ");
            break;
        case R2:
            fprintf(outputPtr, "R R ");
            break;
        case r:
            fprintf(outputPtr, "r ");
            break;
        case ri:
            fprintf(outputPtr, "r' ");
            break;
        case r2:
            fprintf(outputPtr, "r2 ");
            break;
        case B:
            fprintf(outputPtr, "B ");
            break;
        case BI:
            fprintf(outputPtr, "B' ");
            break;
        case B2:
            fprintf(outputPtr, "B B ");
            break;
        case b:
            fprintf(outputPtr, "b ");
            break;
        case bi:
            fprintf(outputPtr, "b' ");
            break;
        case b2:
            fprintf(outputPtr, "b2 ");
            break;
        case D:
            fprintf(outputPtr, "z L z' ");
            break;
        case DI:
            fprintf(outputPtr, "z L' z' ");
            break;
        case D2:
            fprintf(outputPtr, "z L L z' ");
            break;
        case d:
            fprintf(outputPtr, "d ");
            break;
        case di:
            fprintf(outputPtr, "d' ");
            break;
        case d2:
            fprintf(outputPtr, "d2 ");
            break;
        default:
            return 1;
    }
    return 0;
}