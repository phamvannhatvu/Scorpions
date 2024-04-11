#include "./helper.h"
#include "./auto_solver.h"
#include "./manual_solver.h"

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
                if (manual_rubik_solve() == 1)
                {
                    printf("Color reading error, please try again\n");
                }
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
                if (auto_rubik_solve() == 1)
                {
                    printf("Color reading error, please try again\n");
                }
                break;

            default:
                return 0;
            }
        }
    }

    return 0;
}