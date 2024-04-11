#include "./auto_solver.h"

void auto_color_setup()
{
    uint8_t buf_out[20] = "color_setup";
    uint8_t buf_in[200];
    FILE* file_color_ptr = fopen("colors.txt", "w");
    write_usb(buf_out, strlen(buf_out));

    for (int i = 0; i < 6; ++i)
    {
        if (i == 4)
        {
            Sleep(CHANGE_FACE_3_MOVES_DURATION);
        } else if (i == 5)
        {
            Sleep(CHANGE_FACE_2_MOVES_DURATION);
        } else 
        {
            Sleep(CHANGE_FACE_1_MOVE_DURATION);
        }
        read_usb(buf_in, 3);
        printf("%d %d %d\n", buf_in[0], buf_in[1], buf_in[2]); // RGB
        fprintf(file_color_ptr, "%d %d %d\n", buf_in[0], buf_in[1], buf_in[2]); // RGB

        buf_out[0] = 1; // "Change face signal"
        write_usb(buf_out, 1);
    }
    fclose(file_color_ptr);
}

int auto_rubik_solve()
{
    uint8_t buf_out[20] = "rubik_solve";
    uint8_t buf_in[200];
    send_solve_command(buf_out, buf_in);

    printf("Solving...\n");

    for (int i = 0; i < 48; ++i)
    {
        if (i % 8 != 0) // Not changing faces
        {
            if (i % 2 == 0)
            {
                Sleep(READ_COLOR_WITH_TURNING);
            }
        }else if (i != 0) // Changing faces
        {
            if (i / 8 == 4)
            {
                Sleep(CHANGE_FACE_3_MOVES_DURATION);
            } else if (i / 8 == 5)
            {
                Sleep(CHANGE_FACE_2_MOVES_DURATION);
            } else 
            {
                Sleep(CHANGE_FACE_1_MOVE_DURATION);
            }
        }

        for (int j = 0; j < 10; ++j)
        {
            read_usb(buf_in, 3);
            Sleep(1);
            cells_rgb[i][j].red = buf_in[0];
            cells_rgb[i][j].green = buf_in[1];
            cells_rgb[i][j].blue = buf_in[2];
        }

        buf_out[0] = 1; // "Change cell signal"
        write_usb(buf_out, 1);
    }

    uint8_t start_solving;    
    read_usb(&start_solving, 1);
    Sleep(1);
    if (solve_and_print_to_file()) 
    {    
        // Done signal if reading color incorrectly
        char *done = "done";
        write_usb((uint8_t*)done, 4);
        return 1;
    }

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
    fclose(outputPtr);        
    char *done = "done";
    write_usb((uint8_t*)done, 4);
    return 0;
}