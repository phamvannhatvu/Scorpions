#include "./manual_solver.h"

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
        fprintf(file_color_ptr, "%d %d %d\n", buf_in[0], buf_in[1], buf_in[2]);
        colors_rgb[i].red = buf_in[0];
        colors_rgb[i].green = buf_in[1];
        colors_rgb[i].blue = buf_in[2];
    }
    fclose(file_color_ptr);
}

int manual_rubik_solve()
{
    uint8_t buf_out[20] = "rubik_solve";
    uint8_t buf_in[200];
    send_solve_command(buf_out, buf_in);

    printf("Solving...\n");
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

        for (int j = 0; j < 10; ++j)
        {
            read_usb(buf_in, 3);
            Sleep(1);
            cells_rgb[i][j].red = buf_in[0];
            cells_rgb[i][j].green = buf_in[1];
            cells_rgb[i][j].blue = buf_in[2];
        }
    }

    return solve_and_print_to_file();
}