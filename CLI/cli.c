#include "RubikAlgorithm/rubik_alg.h"
#include "USBCommunication/libusb-MinGW-x64/usb.h"
#include "windows.h"

//move r 45 deg clock-wise to read each cell
const int color_read_order[] = {
    35, 11, 40, 22, 51, 26, 42, 13, // (R:35) -> f
    30, 6, 32, 9, 34, 12, 36, 15, // (U:30) -> f
    47, 20, 38, 7, 31, 17, 44, 28, // (L: 47) -> f
    50, 21, 48, 18, 46, 27, 52, 24, // (D: 50) -> f
    // RED (right side) -> r -> f -> GREEN (right side)
    39, 19, 49, 23, 41, 10, 33, 8, // (F: 39)
    // GREEN -> f -> f -> BLUE
    43, 25, 53, 29, 45, 16, 37, 14 // (B: 43)
    // BLUE -> f -> r' -> RED
};

const char * color_by_id[] = {"red", "white", "orange", "yellow", "green", "blue"};

enum SOLVING_MODE {
    AUTO, 
    MANUAL
};

enum OPTION {
    SETUP, 
    SOLVE,
    EXIT
};

void print_color(int i)
{
    if (i < 6)
    {
        printf("%s", color_by_id[i]);
    }else
    {
        printf("Invalid color");
    }
}

void file_print_color(FILE* file_ptr, int i)
{
    if (i < 6)
    {
        fprintf(file_ptr, "%s", color_by_id[i]);
    }else
    {
        fprintf(file_ptr, "Invalid color");
    }
}

void color_setup()
{
    uint8_t buf_out[20] = "color_setup";
    uint8_t buf_in[200];
    FILE* file_color_ptr = fopen("colors.txt", "w");
    write_usb(buf_out, 11);

    for (int i = 0; i < 6; ++i)
    {
        buf_out[0] = 2;
        while (buf_out[0] != 0)
        { 
            printf("Enter 0 and place the cube at ");
            print_color(i);
            printf(" face: ");
            scanf("%d", &buf_out[0]);
        }
        write_usb(buf_out, 1);

        read_usb(buf_in, 3);
        fprintf(file_color_ptr, "%d %d %d\n", buf_in[0], buf_in[1], buf_in[2]); // RGB
    }
    fclose(file_color_ptr);
}

void load_color()
{
    printf("Loading color config from PC...\n");
    uint8_t buf_in[200];
    FILE* file_color_ptr = fopen("colors.txt", "r");

    for (int i = 0; i < 6; ++i)
    {
        Sleep(1);
        buf_in[0] = 0; // NAK
        // Wait for ACK
        while (buf_in[0] == 0)
        {
            read_usb(buf_in, 1);
        }
        uint8_t rgb[3];
        fscanf(file_color_ptr, "%u%u%u", rgb, rgb + 1, rgb + 2);
        write_usb(rgb, 3);
    }
    fclose(file_color_ptr);
}

void rubik_solve()
{
    uint8_t buf_out[20] = "rubik_solve";
    uint8_t buf_in[200];
    write_usb(buf_out, 11);
    Sleep(1);
    read_usb(buf_in, 1);
    if (buf_in[0] == 1)
    {
        Sleep(1);
        load_color();
    }

    printf("Solving...\n");
    enum COLOR cube_color[54];
    cube_color[0] = WHITE;
    cube_color[1] = ORANGE;
    cube_color[2] = GREEN;
    cube_color[3] = RED;
    cube_color[4] = BLUE;
    cube_color[5] = YELLOW;
    for (int i = 0; i < 48; ++i)
    {
        if (i % 8 == 0)
        {
            printf("Place new face\n");
        }
        Sleep(1);
        buf_out[0] = 2;
        while (buf_out[0] != 0)
        { 
            printf("Enter 0 and place the cube at cell %d: ", color_read_order[i]);
            scanf("%d", &buf_out[0]);
        }
        write_usb(buf_out, 1);

        Sleep(1);
        read_usb(buf_in, 1);
        printf("%s\n", color_by_id[buf_in[0]]);
        switch (buf_in[0])
        {
        case 0:
            cube_color[color_read_order[i]] = RED;
            break;
        case 1:
            cube_color[color_read_order[i]] = WHITE;
            break;
        case 2:
            cube_color[color_read_order[i]] = ORANGE;
            break;
        case 3:
            cube_color[color_read_order[i]] = YELLOW;
            break;
        case 4:
            cube_color[color_read_order[i]] = GREEN;
            break;
        case 5:
            cube_color[color_read_order[i]] = BLUE;
            break;
        default:
            break;
        }
    }

    struct CUBE c;
    initCube(&c, STANDARD3X3);
    setCube(&c, STANDARD3X3, cube_color);
    printCube(&c);
    // return;

    // enum MOVE scramble0[20] = {R2, B, UI, R, DI, L2, B, U, FI, L2, B2, L2, DI, LI, F2, R2, U2, F2, UI, FI};
    // enum MOVE scramble1[20] = {D, BI, DI, U2, F, B, UI, R, U2, BI, LI, BI, D2, UI, LI, R2, DI, FI, LI, D2};
    // enum MOVE scramble2[20] = {L2, U2, L2, DI, L2, F2, U2, F2, U, F, RI, B, LI, D2, B2, R2, D, BI, FI, UI};
    // enum MOVE scramble3[20] = {RI, U2, B, D2, R2, FI, DI, BI, R2, U, R, U2, BI, U, D2, B2, LI, D2, B2, UI};
    // moveCubes(&c, 20, scramble0);
    // printCube(&c);

    printf("\ncfopSolve return %d\n", cfopSolve(&c));

    printCube(&c);
    destroyCube(&c);
}

int main(int argc, char *argv[]) {
    enum SOLVING_MODE mode = MANUAL;

    while (1)
    {
        printf("Enter %d to setup, %d to solve or %d to exit: ", SETUP, SOLVE, EXIT);
        enum OPTION option;
        scanf("%d", &option);
        printf("%d\n", option);
        
        switch (option)
        {
        case SETUP:
            color_setup();
            break;
        
        case SOLVE:
            rubik_solve();
            break;

        default:
            return 0;
        }
    }

    return 0;
}