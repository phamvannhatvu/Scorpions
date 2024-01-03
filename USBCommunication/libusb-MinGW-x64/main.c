#include "usb.h"

void print_color(int i)
{
    switch (i)
    {
        case 0:
            printf("red");
            break;
        case 1:
            printf("white");
            break;
        case 2:
            printf("blue");
            break;
        case 3:
            printf("green");
            break;
        case 4:
            printf("yellow");
            break;
        case 5:
            printf("orange");
            break;
        default:
            printf("nooooooooo");
            break;
    }
}

int main(int argc, char *argv[]) {
    int s = 140;
    uint8_t buf_out[20] = "color_setup";
    uint8_t buf_in[200] = "abc";

    if (argc == 2)
    {
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
            printf("Color reading for ");
            print_color(i);
            printf(":\n");

            for (int i = 0; i < 3; ++i)
            {
                switch (i)
                {
                case 0:
                    printf("red ");
                    break;
                case 1:
                    printf("green ");
                    break;
                case 2:
                    printf("blue ");
                    break;
                }
                printf(": %d\n", buf_in[i]);
            }
        }
    }

    while (1)
    {
        int a = 0;
        printf("Enter 0 to read color or 1 to finish: ");
        scanf("%d", &a);
        if (a == 1) break;
        sprintf(buf_out, "read_color");
        write_usb(buf_out, strlen(buf_out));
        read_usb(buf_in, 1);
        print_color(buf_in[0]);
        printf("\n");
    }

    return 0;
}