#include "rubik_alg.h"

int main() {
    struct CUBE c;
    initCube(&c, STANDARD3X3);
    setCube(&c, STANDARD3X3, NULL);

    enum MOVE scramble0[20] = {R2, B, UI, R, DI, L2, B, U, FI, L2, B2, L2, DI, LI, F2, R2, U2, F2, UI, FI};
    enum MOVE scramble1[20] = {D, BI, DI, U2, F, B, UI, R, U2, BI, LI, BI, D2, UI, LI, R2, DI, FI, LI, D2};
    enum MOVE scramble2[20] = {L2, U2, L2, DI, L2, F2, U2, F2, U, F, RI, B, LI, D2, B2, R2, D, BI, FI, UI};
    enum MOVE scramble3[20] = {RI, U2, B, D2, R2, FI, DI, BI, R2, U, R, U2, BI, U, D2, B2, LI, D2, B2, UI};
    moveCubes(&c, 20, scramble0);
    printCube(&c);

    printf("\ncfopSolve return %d\n", cfopSolve(&c));

    printCube(&c);
    destroyCube(&c);
    return 0;
}