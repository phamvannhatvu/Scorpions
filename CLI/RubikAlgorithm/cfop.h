#ifndef _CFOP_H_
#define _CFOP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "move.h"
#include "find.h"

#define CFOPTIMES 4

#define CFOPCROSSES 24
#define CFOPF1LS 24
#define CFOPF2LS 16
#define CFOPOLLS 58
#define CFOPPLLS 22

#define CFOPCROSSCODE 4
#define CFOPF1LCODE 4
#define CFOPF2LCODE 4
#define CFOPOLLCODE 9
#define CFOPPLLCODE 17

#define CFOPPIECE 21
#define CFOPSIDE 6
#define CFOPMOVE 18

static enum COLOR UPCOLOR = NOCOLOR;
static enum COLOR LEFTCOLOR = NOCOLOR;
static enum COLOR FRONTCOLOR = NOCOLOR;
static enum COLOR RIGHTCOLOR = NOCOLOR;
static enum COLOR BACKCOLOR = NOCOLOR;
static enum COLOR DOWNCOLOR = NOCOLOR;

int convertPieceIndexs(int times, int num, int* indexs, int* reIndexs);
int convertPieceSides(int times, int num, enum SIDE* sides, enum SIDE* reSides);
int convertUpCells(int times, int num, int* indexs, int* reIndexs);
int convertUpPieces(int times, int num, int* indexs, int* reIndexs);
int revertMoves(int times, int num, enum MOVE* moves, enum MOVE* reMoves);

int getCrossCode(int* indexs, enum SIDE* sides, char* code);
int getF1LCode(int* indexs, enum SIDE* sides, char* code);
int getF2LCode(int* indexs, enum SIDE* sides, char* code);
int getOLLCode(int* cornerIndex, int* edgeIndex, char* code);
int getPLLCode(int* cornerIndex, int* edgeIndex, char* code);

int cfopSolve(struct CUBE* cube);
int cfopCross(struct CUBE* cube);
int cfopF1L(struct CUBE* cube);
int cfopF2L(struct CUBE* cube);
int cfopOLL(struct CUBE* cube);
int cfopPLL(struct CUBE* cube);

static int INDEXS[CFOPTIMES][CFOPPIECE] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
    {0, 2, 3, 4, 1, 6, 7, 8, 5, 10, 11, 12, 9, 14, 15, 16, 13, 18, 19, 20, 17},
    {0, 3, 4, 1, 2, 7, 8, 5, 6, 11, 12, 9, 10, 15, 16, 13, 14, 19, 20, 17, 18},
    {0, 4, 1, 2, 3, 8, 5, 6, 7, 12, 9, 10, 11, 16, 13, 14, 15, 20, 17, 18, 19}
};

static enum SIDE SIDES[CFOPTIMES][CFOPSIDE] = {
    {UP, LEFT, FRONT, RIGHT, BACK, DOWN},
    {UP, FRONT, RIGHT, BACK, LEFT, DOWN},
    {UP, RIGHT, BACK, LEFT, FRONT, DOWN},
    {UP, BACK, LEFT, FRONT, RIGHT, DOWN}
};

static enum MOVE MOVES[CFOPTIMES][CFOPMOVE] = {
    {U, UI, U2, L, LI, L2, F, FI, F2, R, RI, R2, B, BI, B2, D, DI, D2},
    {U, UI, U2, F, FI, F2, R, RI, R2, B, BI, B2, L, LI, L2, D, DI, D2},
    {U, UI, U2, R, RI, R2, B, BI, B2, L, LI, L2, F, FI, F2, D, DI, D2},
    {U, UI, U2, B, BI, B2, L, LI, L2, F, FI, F2, R, RI, R2, D, DI, D2}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////       CROSS        ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

static char* CROSSCODES[CFOPCROSSES] = {
    "091", "092", "101", "103", "111", "114", "121", "125",
    "132", "133", "144", "143", "154", "155", "162", "165",
    "176", "172", "186", "183", "196", "194", "206", "205"
};

static enum MOVE CROSS00[1] = {L2};
static enum MOVE CROSS01[4] = {U, B, LI, BI};
static enum MOVE CROSS02[2] = {U, L2};
static enum MOVE CROSS03[3] = {FI, L, F};
static enum MOVE CROSS04[2] = {U2, L2};
static enum MOVE CROSS05[4] = {U, FI, L, F};
static enum MOVE CROSS06[2] = {UI, L2};
static enum MOVE CROSS07[3] = {B, LI, BI};
static enum MOVE CROSS08[3] = {D, FI, DI};
static enum MOVE CROSS09[1] = {L};
static enum MOVE CROSS10[3] = {D, F, DI};
static enum MOVE CROSS11[3] = {F2, L, F2};
static enum MOVE CROSS12[3] = {DI, BI, D};
static enum MOVE CROSS13[3] = {B2, LI, B2};
static enum MOVE CROSS14[3] = {DI, B, D};
static enum MOVE CROSS15[1] = {LI};
static enum MOVE CROSS16[1] = {NOMOVE};
static enum MOVE CROSS17[4] = {LI, D, FI, DI};
static enum MOVE CROSS18[3] = {F2, U, L2};
static enum MOVE CROSS19[2] = {F, L};
static enum MOVE CROSS20[3] = {R2, U2, L2};
static enum MOVE CROSS21[4] = {R, D, F, DI};
static enum MOVE CROSS22[3] = {B2, UI, L2};
static enum MOVE CROSS23[2] = {BI, LI};

static enum MOVE* CROSSSOLVE[24] = {
    CROSS00, CROSS01, CROSS02, CROSS03, CROSS04, CROSS05, CROSS06, CROSS07,
    CROSS08, CROSS09, CROSS10, CROSS11, CROSS12, CROSS13, CROSS14, CROSS15,
    CROSS16, CROSS17, CROSS18, CROSS19, CROSS20, CROSS21, CROSS22, CROSS23
};

static int CROSSSIZE[24] = {
    1, 4, 2, 3, 2, 4, 2, 3,
    3, 1, 3, 3, 3, 3, 3, 1,
    0, 4, 3, 2, 3, 4, 3, 2
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////        F1L         ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

static char* F1LCODES[CFOPF1LS] = {
    "011", "012", "013", "021", "023", "024", "031", "034",
    "035", "041", "045", "042", "056", "053", "052", "066",
    "064", "063", "076", "075", "074", "086", "082", "085"
};

static enum MOVE F1L00[5]   = {L2, UI, L2, U, L2};
static enum MOVE F1L01[3]   = {LI, UI, L};
static enum MOVE F1L02[3]   = {F, U, FI};
static enum MOVE F1L03[6]   = {U, L2, UI, L2, U, L2};
static enum MOVE F1L04[4]   = {U, LI, UI, L};
static enum MOVE F1L05[4]   = {U, F, U, FI};
static enum MOVE F1L06[6]   = {U2, L2, UI, L2, U, L2};
static enum MOVE F1L07[4]   = {U2, LI, UI, L};
static enum MOVE F1L08[4]   = {U2, F, U, FI};
static enum MOVE F1L09[6]   = {UI, L2, UI, L2, U, L2};
static enum MOVE F1L10[4]   = {UI, LI, UI, L};
static enum MOVE F1L11[4]   = {UI, F, U, FI};
static enum MOVE F1L12[1]   = {NOMOVE};
static enum MOVE F1L13[6]   = {LI, U, L, F, U, FI};
static enum MOVE F1L14[6]   = {F, UI, FI, LI, UI, L};
static enum MOVE F1L15[6]   = {R, U, RI, LI, UI, L};
static enum MOVE F1L16[5]   = {R, LI, U, L, RI};
static enum MOVE F1L17[5]   = {FI, UI, F2, U2, FI};
static enum MOVE F1L18[5]   = {B, F, U2, FI, BI};
static enum MOVE F1L19[5]   = {B, LI, U2, L, BI};
static enum MOVE F1L20[5]   = {RI, F, U2,  FI, R};
static enum MOVE F1L21[6]   = {BI, UI, B, F, U, FI};
static enum MOVE F1L22[5]   = {L, U, L2, U2, L};
static enum MOVE F1L23[5]   = {BI, F, UI, FI, B};

static enum MOVE* F1LSOLVE[24] = {
    F1L00, F1L01, F1L02, F1L03, F1L04, F1L05, F1L06, F1L07,
    F1L08, F1L09, F1L10, F1L11, F1L12, F1L13, F1L14, F1L15,
    F1L16, F1L17, F1L18, F1L19, F1L20, F1L21, F1L22, F1L23
};

static int F1LSIZE[24] = {
    5, 3, 3, 6, 4, 4, 6, 4,
    4, 6, 4, 4, 0, 6, 6, 6,
    5, 5, 5, 5, 5, 6, 5, 5
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////        F2L         ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

static char* F2LCODES[CFOPF2LS] = {
    "091", "092", "101", "103", "111", "114", "121", "125",
    "132", "133", "144", "143", "154", "155", "162", "165"
};

static enum MOVE F2L00[8]   = {U2, LI, U, L, FI, L, F, LI};
static enum MOVE F2L01[8]   = {U, F, UI, FI, L, FI, LI, F};
static enum MOVE F2L02[8]   = {UI, LI, U, L, FI, L, F, LI};
static enum MOVE F2L03[8]   = {U2, F, UI, FI, L, FI, LI, F};
static enum MOVE F2L04[7]   = {LI, U, L, FI, L, F, LI};
static enum MOVE F2L05[8]   = {UI, F, UI, FI, L, FI, LI, F};
static enum MOVE F2L06[8]   = {U, LI, U, L, FI, L, F, LI};
static enum MOVE F2L07[7]   = {F, UI, FI, L, FI, LI, F};
static enum MOVE F2L08[1]   = {NOMOVE};
static enum MOVE F2L09[15]  = {LI, U, L, FI, L, F, LI, U, LI, U, L, FI, L, F, LI};
static enum MOVE F2L10[5]   = {F2, U2, F2, U2, F2};
static enum MOVE F2L11[15]  = {R, UI, RI, F, RI, FI, R, U, LI, U, L, FI, L, F, LI};
static enum MOVE F2L12[15]  = {B, UI, BI, R, BI, RI, B, U2, LI, U, L, FI, L, F, LI};
static enum MOVE F2L13[15]  = {RI, U, R, BI, R, B, RI, UI, LI, U, L, FI, L, F, LI};
static enum MOVE F2L14[5]   = {L2, U2, L2, U2, L2};
static enum MOVE F2L15[15]  = {L, UI, LI, B, LI, BI, L, UI, LI, U, L, FI, L, F, LI};

static enum MOVE* F2LSOLVE[16] = {
    F2L00, F2L01, F2L02, F2L03, F2L04, F2L05, F2L06, F2L07,
    F2L08, F2L09, F2L10, F2L11, F2L12, F2L13, F2L14, F2L15
};

static int F2LSIZE[CFOPF2LS] = {
    8, 8, 8, 8, 7, 8, 8, 7,
    0, 15, 5, 15, 15, 15, 5, 15
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////        OLL         ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

static char* OLLCODES[CFOPOLLS] = {
    "00000000", "12121111", "11221111", "10111111", "22021111", "11100110", "22021100", "01110110",
    "20221100", "20220110", "11010011", "11100011", "22021001", "01110101", "20220101", "11100101",
    "22020101", "10201111", "00211111", "12001111", "00001111", "21210000", "11220000", "21000000",
    "01200000", "20100000", "22200000", "11010000", "00001001", "12000011", "12001001", "20011100",
    "20011001", "20010101", "00120101", "20101001", "10201100", "20100110", "02010110", "02010101",
    "10200101", "21001001", "10020110", "02100011", "10021001", "10020101", "02101010", "22111100",
    "11220110", "11221100", "22110110", "11220101", "22111010", "12120110", "12121100", "12121010",
    "12120101", "00000101"
};

static enum MOVE OLL00[1]   = {NOMOVE};
static enum MOVE OLL01[11]  = {R, U2, R2, F, R, FI, U2, RI, F, R, FI};
static enum MOVE OLL02[12]  = {F, R, U, RI, UI, FI, B, U, L, UI, LI, BI};
static enum MOVE OLL03[13]  = {B, U, L, UI, LI, BI, UI, F, R, U, RI, UI, FI};
static enum MOVE OLL04[13]  = {B, U, L, UI, LI, BI, U, F, R, U, RI, UI, FI};
static enum MOVE OLL05[7]   = {RI, F2, L, F, LI, F, R};
static enum MOVE OLL06[7]   = {L, F2, RI, FI, R, FI, LI};
static enum MOVE OLL07[7]   = {L, F, RI, F, R, F2, LI};
static enum MOVE OLL08[8]   = {R, U2, RI, U2, RI, F, R, FI};
static enum MOVE OLL09[11]  = {R, U, RI, UI, RI, F, R2, U, RI, UI, FI};
static enum MOVE OLL10[11]  = {R, U, RI, U, RI, F, R, FI, R, U2, RI};
static enum MOVE OLL11[12]  = {FI, LI, UI, L, U, F, R, B, U, BI, UI, RI};
static enum MOVE OLL12[13]  = {F, R, U, RI, UI, FI, U, F, R, U, RI, UI, FI};
static enum MOVE OLL13[10]  = {L, FI, LI, UI, L, F, LI, FI, U, F};
static enum MOVE OLL14[10]  = {RI, F, R, U, RI, FI, R, F, UI, FI};
static enum MOVE OLL15[10]  = {RI, FI, R, LI, UI, L, U, RI, F, R};
static enum MOVE OLL16[10]  = {L, F, LI, R, U, RI, UI, L, FI, LI};
static enum MOVE OLL17[13]  = {R, U, RI, U, RI, F, R, FI, U2, RI, F, R, FI};
static enum MOVE OLL18[11]  = {F, R, U, RI, U, FI, U2, FI, L, F, LI};
static enum MOVE OLL19[12]  = {R, LI, B, R, B, RI, BI, L, R2, F, R, FI};
static enum MOVE OLL20[13]  = {R, LI, B, R, B, RI, BI, R2, L2, F, R, FI, LI};
static enum MOVE OLL21[11]  = {R, U2, RI, UI, R, U, RI, UI, R, UI, RI};
static enum MOVE OLL22[9]   = {R, U2, R2, UI, R2, UI, R2, U2, R};
static enum MOVE OLL23[9]   = {R2, D, RI, U2, R, DI, RI, U2, RI};
static enum MOVE OLL24[8]   = {RI, FI, L, F, R, FI, LI, F};
static enum MOVE OLL25[8]   = {RI, F, R, BI, RI, FI, R, B};
static enum MOVE OLL26[7]   = {RI, UI, R, UI, RI, U2, R};
static enum MOVE OLL27[7]   = {L, U, LI, U, L, U2, LI};
static enum MOVE OLL28[11]  = {RI, L, F, R, LI, U2, RI, L, F, R, LI};
static enum MOVE OLL29[13]  = {R, LI, B, R, B, RI, BI, RI, U, R, UI, RI, L};
static enum MOVE OLL30[11]  = {R2, U, RI, BI, R, UI, R2, U, R, B, RI};
static enum MOVE OLL31[9]   = {RI, UI, F, U, R, UI, RI, FI, R};
static enum MOVE OLL32[9]   = {R, U, BI, UI, RI, U, R, B, RI};
static enum MOVE OLL33[8]   = {R, U, RI, UI, RI, F, R, FI};
static enum MOVE OLL34[11]  = {R, U, R2, UI, RI, F, R, U, R, UI, FI};
static enum MOVE OLL35[9]   = {R, U2, R2, F, R, FI, R, U2, RI};
static enum MOVE OLL36[12]  = {LI, UI, L, UI, LI, U, L, U, L, FI, LI, F};
static enum MOVE OLL37[9]   = {F, R, UI, RI, UI, R, U, RI, FI};
static enum MOVE OLL38[12]  = {R, U, RI, U, R, UI, RI, UI, RI, F, R, FI};
static enum MOVE OLL39[9]   = {L, FI, LI, UI, L, U, F, UI, LI};
static enum MOVE OLL40[9]   = {RI, F, R, U, RI, UI, FI, U, R};
static enum MOVE OLL41[11]  = {R, UI, RI, U2, R, U, B, UI, BI, UI, RI};
static enum MOVE OLL42[12]  = {RI, U2, R, U, RI, U, R2, B, U, BI, UI, RI};
static enum MOVE OLL43[6]   = {BI, UI, RI, U, R, B};
static enum MOVE OLL44[6]   = {B, U, L, UI, LI, BI};
static enum MOVE OLL45[6]   = {F, R, U, RI, UI, FI};
static enum MOVE OLL46[8]   = {RI, UI, RI, F, R, FI, U, R};
static enum MOVE OLL47[12]  = {RI, UI, RI, F, R, FI, RI, F, R, FI, U, R};
static enum MOVE OLL48[10]  = {F, R, U, RI, UI, R, U, RI, UI, FI};
static enum MOVE OLL49[10]  = {RI, F, RI, FI, R2, U2, BI, R, B, RI};
static enum MOVE OLL50[9]   = {RI, F, R2, BI, R2, FI, R2, B, RI};
static enum MOVE OLL51[10]  = {B, U, L, UI, LI, U, L, UI, LI, BI};
static enum MOVE OLL52[10]  = {R, U, RI, U, R, UI, B, UI, BI, RI};
static enum MOVE OLL53[11]  = {RI, FI, L, FI, LI, F, L, FI, LI, F2, R};
static enum MOVE OLL54[11]  = {L, F, RI, F, R, FI, RI, F, R, F2, LI};
static enum MOVE OLL55[11]  = {R, U2, R2, UI, R, UI, RI, U2, F, R, FI};
static enum MOVE OLL56[12]  = {F, R, U, RI, UI, R, FI, L, F, RI, FI, LI};
static enum MOVE OLL57[10]  = {R, U, RI, UI, RI, L, F, R, FI, LI};

static enum MOVE* OLLSOLVE[CFOPOLLS] = {
    OLL00, OLL01, OLL02, OLL03, OLL04, OLL05, OLL06, OLL07,
    OLL08, OLL09, OLL10, OLL11, OLL12, OLL13, OLL14, OLL15,
    OLL16, OLL17, OLL18, OLL19, OLL20, OLL21, OLL22, OLL23,
    OLL24, OLL25, OLL26, OLL27, OLL28, OLL29, OLL30, OLL31,
    OLL32, OLL33, OLL34, OLL35, OLL36, OLL37, OLL38, OLL39,
    OLL40, OLL41, OLL42, OLL43, OLL44, OLL45, OLL46, OLL47,
    OLL48, OLL49, OLL50, OLL51, OLL52, OLL53, OLL54, OLL55,
    OLL56, OLL57
};

static int OLLSIZE[CFOPOLLS] = {
    0, 11, 12, 13, 13, 7, 7, 7,
    8, 11, 11, 12, 13, 10, 10, 10,
    10, 13, 11, 12, 13, 11, 9, 9,
    8, 8, 7, 7, 11, 13, 11, 9,
    9, 8, 11, 9, 12, 9, 12, 9,
    9, 11, 12, 6, 6, 6, 8, 12,
    10, 10, 9, 10, 10, 11, 11, 11,
    12, 10
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////        PLL         ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

static char* PLLCODES[CFOPPLLS] = {
    "0102030409101112", "0102030411091012", "0102030410110912", "0102030412111009",
    "0102030411120910", "0103040209101112", "0301020409101112", "0403020109101112",
    "0103020411100912", "0102040311100912", "0102040312101109", "0103020409111012",
    "0102040310091112", "0102040309111012", "0104030209101211", "0104030212101109",
    "0104030209121110", "0302010409121110", "0302040112100911", "0104020309111210",
    "0401030210110912", "0302040112091110"
};

static enum MOVE PLL00[1]   = {NOMOVE};
static enum MOVE PLL01[11]  = {R, UI, R, U, R, U, R, UI, RI, UI, R2};
static enum MOVE PLL02[11]  = {R2, U, R, U, RI, UI, RI, UI, RI, U, RI};
static enum MOVE PLL03[15]  = {R2, L2, D, R2, L2, U, R, LI, F2, R2, L2, B2, R, LI, U2};
static enum MOVE PLL04[11]  = {R2, L2, D, R2, L2, U2, R2, L2, D, R2, L2};
static enum MOVE PLL05[9]   = {RI, F, RI, B2, R, FI, RI, B2, R2};
static enum MOVE PLL06[9]   = {R, BI, R, F2, RI, B, R, F2, R2};
static enum MOVE PLL07[16]  = {R, BI, RI, F, R, B, RI, FI, R, B, RI, F, R, BI, RI, FI};
static enum MOVE PLL08[14]  = {R, U, RI, UI, RI, F, R2, UI, RI, UI, R, U, RI, FI};
static enum MOVE PLL09[15]  = {RI, U, R, UI, R2, FI, UI, F, U, R, F, RI, FI, R2, UI};
static enum MOVE PLL10[11]  = {RI, U, LI, U2, R, UI, RI, U2, L, R, UI};
static enum MOVE PLL11[14]  = {R, U, RI, FI, R, U, RI, UI, RI, F, R2, UI, RI, UI};
static enum MOVE PLL12[14]  = {L, U2, LI, U2, L, FI, LI, UI, L, U, L, F, L2, U};
static enum MOVE PLL13[14]  = {RI, U2, R, U2, RI, F, R, U, RI, UI, RI, FI, R2, UI};
static enum MOVE PLL14[14]  = {RI, U, RI, UI, BI, D, BI, DI, B2, RI, BI, R, B, R};
static enum MOVE PLL15[17]  = {F, R, UI, RI, UI, R, U, RI, FI, R, U, RI, UI, RI, F, R, FI};
static enum MOVE PLL16[15]  = {L, UI, R, U2, LI, U, RI, L, UI, R, U2, LI, U, RI, U};
static enum MOVE PLL17[15]  = {RI, U, LI, U2, R, UI, L, RI, U, LI, U2, R, UI, L, UI};
static enum MOVE PLL18[12]  = {R2, D, BI, U, BI, UI, B, DI, R2, FI, U, F};
static enum MOVE PLL19[12]  = {LI, UI, L, F2, D, RI, U, R, UI, R, DI, F2};
static enum MOVE PLL20[12]  = {R2, DI, F, UI, F, U, FI, D, R2, B, UI, BI};
static enum MOVE PLL21[12]  = {R, U, RI, F2, DI, L, UI, LI, U, LI, D, F2};

static enum MOVE* PLLSOLVE[CFOPPLLS] = {
    PLL00, PLL01, PLL02, PLL03, PLL04, PLL05, PLL06, PLL07,
    PLL08, PLL09, PLL10, PLL11, PLL12, PLL13, PLL14, PLL15,
    PLL16, PLL17, PLL18, PLL19, PLL20, PLL21
};

static int PLLSIZE[CFOPPLLS] = {
    0, 11, 11, 15, 11, 9, 9, 16,
    14, 15, 11, 14, 14, 14, 14, 17,
    15, 15, 12, 12, 12, 12
};

#endif