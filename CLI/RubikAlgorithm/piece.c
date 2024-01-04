#include "piece.h"

int initPiece(struct PIECE* piece, enum TYPE type) {
    if (piece == NULL) return 1;
    piece->type = type;
    piece->cells = malloc(piece->type * sizeof(struct CELL));
    for (int i = 0; i < piece->type; i ++) {
        if (initCell(piece->cells + i)) return 1;
    }
    return 0;
}

int destroyPiece(struct PIECE* piece) {
    if (piece == NULL) return 1;
    for (int i = 0; i < piece->type; i ++) {
        if (destroyCell(piece->cells + i)) return 1;
    }
    free(piece->cells);
    piece->cells = NULL;
    piece->type = NOTYPE;
    return 0;
}

int setPiece(struct PIECE* piece, enum TYPE type, enum COLOR* colors) {
    if (piece == NULL || colors == NULL) return 1;
    piece->type = type;
    for (int i = 0; i < piece->type; i ++) {
        if (setCell(piece->cells + i, colors[i])) return 1;
    }
    return 0;
}

int coppyPiece(struct PIECE* source, struct PIECE* destination) {
    if (source == NULL || destination == NULL) return 1;
    if (source->type != destination->type) return 1;
    for (int i = 0; i < source->type; i ++) {
        if (coppyCell(source->cells + i, destination->cells + i)) return 1;
    }
    return 0;
}

int comparePiece(struct PIECE* piece1, struct PIECE* piece2, int* result) {
    if (piece1 == NULL || piece2 == NULL || result == NULL) return 1;
    if (piece1->type != piece2->type) {
        *result = 0;
        return 0;
    }
    int cindex = 0;
    int flag = 0;
    for (cindex = 0; cindex < piece2->type; cindex ++) {
        if (compareCell(piece1->cells, piece2->cells + cindex, &flag)) return 1;
        if (flag == 1) break;
    }
    if (flag == 0) {
        *result = 0;
        return 0;
    }
    for (int i = 1; i < piece1->type; i ++) {
        if (compareCell(piece1->cells + i, piece2->cells + (i + cindex) % piece2->type, &flag)) return 1;
        if (flag == 0) {
            *result = 0;
            return 0;
        }
    }
    *result = 1;
    return 0;
}