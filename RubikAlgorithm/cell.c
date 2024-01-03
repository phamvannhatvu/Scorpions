#include "cell.h"

int initCell(struct CELL* cell) {
    if (cell == NULL) return 1;
    cell->color = NOCOLOR;
    cell->side = NOSIDE;
    return 0;
}

int destroyCell(struct CELL* cell) {
    if (cell == NULL) return 1;
    cell->color = NOCOLOR;
    cell->side = NOSIDE;
    return 0;
}

int setCell(struct CELL* cell, enum COLOR color) {
    if (cell == NULL) return 1;
    cell->color = color;
    return 0;
}

int coppyCell(struct CELL* source, struct CELL* destination) {
    if (source == NULL || destination == NULL) return 1;
    destination->color = source->color;
    return 0;
}

int compareCell(struct CELL* cell1, struct CELL* cell2, int* result) {
    if (cell1 == NULL || cell2 == NULL) return 1;
    if (cell1->color != cell2->color) *result = 0;
    else *result = 1;
    return 0;
}

int getColor(struct CELL* cell, enum COLOR* color) {
    if (cell == NULL || color == NULL) return 1;
    *color = cell->color;
    return 0;
}

int getColorCode(struct CELL* cell, char* colorCode) {
    if (cell == NULL || colorCode == NULL) return 1;
    switch (cell->color) {
        case NOCOLOR:
            *colorCode = ' ';
            break;
        case WHITE:
            *colorCode = 'W';
            break;
        case ORANGE:
            *colorCode = 'O';
            break;
        case GREEN:
            *colorCode = 'G';
            break;
        case RED:
            *colorCode = 'R';
            break;
        case BLUE:
            *colorCode = 'B';
            break;
        case YELLOW:
            *colorCode = 'Y';
            break;
        default:
            return 1;
    }
    return 0;
}