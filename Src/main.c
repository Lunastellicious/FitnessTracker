#include <stdio.h>
#include "./include/data.h"
#include "./include/linear_regression.h"
#include "./include/generate_run.h"
#include "./include/run_data.h"
#include "./include/recommends.h"

int main(void)
{
    printf("Hello, main!\n");

    generateMain();
    regression();

    return 0;

}