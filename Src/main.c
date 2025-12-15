#include <stdio.h>
#include "./include/data.h"
#include "./include/linear_regression.h"
#include "./include/run_data.h"

int main(void)
{
    Database current;
    set_HRmax(&current, 195);
    runData(20,30,3500, &current);
    printf("Hello, World!\n");

    regression();

    printf("Also\nCongratulations your code is not borked: %d\n", current.HRmax);
    printf("also congratulations x2 runData also works:\nDistance: %lf \nDuration: %lf\n", current.distance, current.duration);
    return 0;

}