#include "RubikAlgorithm/rubik_alg.h"
#include "USBCommunication/libusb-MinGW-x64/usb.h"
#include "windows.h"
#include "string.h"

//move r 45 deg clock-wise to read each cell
const int color_read_order[] = {
    35, 13, 42, 26, 51, 22, 40, 11, //11, 40, 22, 51, 26, 42, 13, // (R:35) -> f
    30, 15, 36, 12, 34, 9, 32, 6, //6, 32, 9, 34, 12, 36, 15, // (U:30) -> f
    47, 28, 44, 17, 31, 7, 38, 20, //20, 38, 7, 31, 17, 44, 28, // (L: 47) -> f
    50, 24, 52, 27, 46, 18, 48, 21, //21, 48, 18, 46, 27, 52, 24, // (D: 50) -> f
    // RED (right side) -> r -> f -> GREEN (right side)
    39, 8, 33, 10, 41, 23, 49, 19, // 19, 49, 23, 41, 10, 33, 8, // (F: 39)
    // GREEN -> f -> f -> BLUE
    43, 14, 37, 16, 45, 29, 53, 25, //25, 53, 29, 45, 16, 37, 14 // (B: 43)
    // BLUE -> f -> r' -> RED
};

const char * color_by_id[] = {"red", "white", "orange", "yellow", "green", "blue"};

enum SOLVING_MODE {
    MANUAL,
    AUTO
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

void manual_color_setup()
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

void send_solve_command(uint8_t buf_out[], uint8_t buf_in[])
{
    write_usb(buf_out, 11);
    Sleep(1);
    read_usb(buf_in, 1);
    if (buf_in[0] == 1)
    {
        Sleep(1);
        load_color();
    }
}

void set_cube_color(enum COLOR cube_color[], uint8_t buf_in[], uint8_t index_color_read)
{
    switch (buf_in[0])
    {
    case 0:
        cube_color[color_read_order[index_color_read]] = RED;
        break;
    case 1:
        cube_color[color_read_order[index_color_read]] = WHITE;
        break;
    case 2:
        cube_color[color_read_order[index_color_read]] = ORANGE;
        break;
    case 3:
        cube_color[color_read_order[index_color_read]] = YELLOW;
        break;
    case 4:
        cube_color[color_read_order[index_color_read]] = GREEN;
        break;
    case 5:
        cube_color[color_read_order[index_color_read]] = BLUE;
        break;
    default:
        break;
    }
}

void init_centers(enum COLOR cube_color[])
{
    cube_color[0] = WHITE;
    cube_color[1] = ORANGE;
    cube_color[2] = GREEN;
    cube_color[3] = RED;
    cube_color[4] = BLUE;
    cube_color[5] = YELLOW;
}

void print_solution_to_file(enum COLOR cube_color[])
{
    // Empty the output file
    FILE* outputPtr = fopen("output.txt", "w");
    fclose(outputPtr);
    struct CUBE c;
    initCube(&c, STANDARD3X3);
    setCube(&c, STANDARD3X3, cube_color);
    cfopSolve(&c);
    printCube(&c);
    destroyCube(&c);
}

void manual_rubik_solve()
{
    uint8_t buf_out[20] = "rubik_solve";
    uint8_t buf_in[200];
    send_solve_command(buf_out, buf_in);

    printf("Solving...\n");
    enum COLOR cube_color[54];
    init_centers(cube_color);
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
        set_cube_color(cube_color, buf_in, i);
    }

    print_solution_to_file(cube_color);
}

void auto_color_setup()
{
    uint8_t buf_out[20] = "color_setup";
    uint8_t buf_in[200];
    FILE* file_color_ptr = fopen("colors.txt", "w");
    write_usb(buf_out, strlen(buf_out));

    for (int i = 0; i < 6; ++i)
    {
        read_usb(buf_in, 3);
        fprintf(file_color_ptr, "%d %d %d\n", buf_in[0], buf_in[1], buf_in[2]); // RGB

        buf_out[0] = 1; // "Change face signal"
        write_usb(buf_out, 1);
    }
    fclose(file_color_ptr);
}

void auto_rubik_solve()
{
    uint8_t buf_out[20] = "rubik_solve";
    uint8_t buf_in[200];
    send_solve_command(buf_out, buf_in);

    printf("Solving...\n");
    enum COLOR cube_color[54];
    init_centers(cube_color);

    for (int i = 0; i < 48; ++i)
    {
        Sleep(1);
        read_usb(buf_in, 1);
        printf("%s\n", color_by_id[buf_in[0]]);
        set_cube_color(cube_color, buf_in, i);

        buf_out[0] = 1; // "Change cell signal"
        write_usb(buf_out, 1);
    }

    print_solution_to_file(cube_color);

    uint8_t start_solving;
    read_usb(&start_solving, 1);
    Sleep(1);
    FILE* outputPtr = fopen("output.txt", "r");
    char move[10];
    while (fscanf(outputPtr, "%s", &move) != EOF)
    {
        write_usb((uint8_t*)move, (uint16_t)strlen(move));
        Sleep(1);

        uint8_t ack;
        read_usb(&ack, 1);
        Sleep(1);
    }
    // Done signal
    char *done = "done";
    write_usb((uint8_t*)done, 4);
    fclose(outputPtr);
}

int main(int argc, char *argv[]) {
    enum SOLVING_MODE mode = MANUAL;
    printf("Enter %d to select manual mode or enter %d to select auto mode: \n", MANUAL, AUTO);
    scanf("%d", &mode);
    write_usb((uint8_t*)&mode, 1);

    if (mode == MANUAL)
    {
        while (1)
        {
            printf("Enter %d to setup, %d to solve or %d to exit: ", SETUP, SOLVE, EXIT);
            enum OPTION option;
            scanf("%d", &option);
            printf("%d\n", option);
            
            switch (option)
            {
            case SETUP:
                manual_color_setup();
                break;
            
            case SOLVE:
                manual_rubik_solve();
                break;

            default:
                return 0;
            }
        }
    }else
    {
        printf("auto\n");
        
        while (1)
        {
            printf("Enter %d to setup, %d to solve or %d to exit: ", SETUP, SOLVE, EXIT);
            enum OPTION option;
            scanf("%d", &option);
            printf("%d\n", option);
            
            switch (option)
            {
            case SETUP:
                auto_color_setup();
                break;
            
            case SOLVE:
                auto_rubik_solve();
                break;

            default:
                return 0;
            }
        }
    }

    return 0;
}