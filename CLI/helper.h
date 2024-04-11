#ifndef HELPER_H
#define HELPER_H

#include "RubikAlgorithm/rubik_alg.h"
#include "USBCommunication/libusb-MinGW-x64/usb.h"
#include "windows.h"
#include "string.h"
#include "math.h"

enum SOLVING_MODE 
{
    MANUAL,
    AUTO
};

enum OPTION 
{
    SETUP, 
    SOLVE,
    EXIT
};

typedef struct 
{
    uint8_t red;
    uint8_t green;
    uint8_t blue; 
} rgb;

extern int color_loaded;
extern rgb colors_rgb[6];
extern const char * color_by_id[];
extern const int color_read_order[];
extern rgb cells_rgb[48][10];

void print_color(int i);
void file_print_color(FILE* file_ptr, int i);
void send_solve_command(uint8_t buf_out[], uint8_t buf_in[]);
int solve_and_print_to_file();

#endif