#include "./helper.h"

const char * color_by_id[] = {"green", "yellow", "blue", "white", "red", "orange"};
int color_loaded = 0;
rgb colors_rgb[6];
rgb cells_rgb[48][10];

//move r 45 deg clock-wise to read each cell
const int color_read_order[] = {
    39, 8, 49, 19, 41, 23, 33, 10,
    46, 18, 52, 27, 50, 24, 48, 21,
    45, 29, 37, 16, 43, 14, 53, 25,
    30, 15, 32, 6, 34, 9, 36, 12,
    51, 22, 42, 26, 35, 13, 40, 11,
    47, 28, 38, 20, 31, 7, 44, 17,
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

void load_color()
{
    printf("Loading color config from PC...\n");
    uint8_t buf_in[200];
    FILE* file_color_ptr = fopen("colors.txt", "r");
    for (int i = 0; i < 6; ++i)
    {
        uint8_t rgb[3];
        fscanf(file_color_ptr, "%u%u%u", rgb, rgb + 1, rgb + 2);
        colors_rgb[i].red = rgb[0];
        colors_rgb[i].green = rgb[1];
        colors_rgb[i].blue = rgb[2];
    }
    fclose(file_color_ptr);
}

void send_solve_command(uint8_t buf_out[], uint8_t buf_in[])
{
    write_usb(buf_out, 11);
    Sleep(1);
    if (color_loaded == 0)
    {
        color_loaded = 1;
        load_color();
    }
}

void set_cube_color(enum COLOR cube_color[], uint8_t color, uint8_t index_color_read)
{
    switch (color)
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
    cube_color[0] = GREEN;
    cube_color[1] = YELLOW;
    cube_color[2] = BLUE;
    cube_color[3] = WHITE;
    cube_color[4] = RED;
    cube_color[5] = ORANGE;
}

int solve_and_print_to_file()
{
    enum COLOR cube_color[54];
    init_centers(cube_color);

    for (int cell = 0; cell < 48; ++cell) 
    {
        enum COLOR color = GREEN;
        int min_rgb_diff = 255;
        for (int color_index = 0; color_index < 6; ++color_index) 
        {
            rgb color_rgb = colors_rgb[color_index];
            for (int sample = 0; sample < 10; ++sample)
            {
                rgb sample_rgb = cells_rgb[cell][sample];
                int current_rgb_diff = max(abs(color_rgb.red - sample_rgb.red), 
                    max(abs(color_rgb.green - sample_rgb.green), abs(color_rgb.red - sample_rgb.red)));
                if (current_rgb_diff < min_rgb_diff)
                {
                    // color at the center cell of each face
                    color = cube_color[color];
                    min_rgb_diff = current_rgb_diff;
                }
            }
        }
        set_cube_color(cube_color, color, color_read_order[cell]);
    }

    // Empty the output file
    FILE* outputPtr = fopen("output.txt", "w");
    fclose(outputPtr);
    struct CUBE c;
    initCube(&c, STANDARD3X3);
    setCube(&c, STANDARD3X3, cube_color);
    if (cfopSolve(&c) == 1)
    {
        destroyCube(&c);
        return 1;
    }
    printCube(&c);
    destroyCube(&c);
    return 0;
}
