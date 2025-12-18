#include <stdio.h>
#include "./include/data.h"
#include "./include/linear_regression.h"
#include "./include/run_data.h"
#include "./include/recommends.h"
#include "./include/generate_run.h"

int main(void)
{
    Database current;
    regressionResult result;

    generateMain(&current);
    // runData(30, 60, &current);
    //regression(&result);
    recommend(&current, &result);

    return 0;
}