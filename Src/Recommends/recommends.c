#include "../include/recommends.h"
#include <stdio.h>
#include "../include/linear_regression.h"
#include <math.h>

// TODO: write out output statements to gather based off the relevant data
// TODO: print the appropriate collection of output statements to the console
// TODO: try to format the console output in a not super ugly way





void metricsToImprove(double vo2Max, regressionResult a, double distance, double time, double heartRate, int* vo2MaxPos, int* runSPeed, int* runLength);


int evaluateRun(double vo2Max);
//void print(int scenario, double distance, double time, double heartRate, double vo2Max);



// distance values to be given in KM
void recommend(double distance, double vo2Max, double heartRate, double time, regressionResult a ) {

    int runSPeed = 0;
    int vo2MaxPos = 0;
    int runLength = 0;

    int runValue = 0; // determines the value of a run: 0 = bad: 1 = ok: 2 = good: 3 = excellent: 4 being perfect
    runValue = evaluateRun(vo2Max);

    // TODO: call metrics to improve and call print
    /*
    if (runValue == 4){
        print(runValue, distance, time, heartRate, vo2Max);
    } else {
        metricsToImprove(vo2Max, a, distance, time, heartRate, &vo2MaxPos, &runSPeed, &runLength);

    }*/

}

int evaluateRun(double vo2Max) {
    int runValue = 0;
    if (vo2Max -36.1 <= 0) {
        runValue =  0;
        return runValue;
    } else if (vo2Max -39.5 <= 0) {
        runValue = 1;
        return runValue;
    }else if (vo2Max -43.9 <= 0) {
        runValue = 2;
        return runValue;
    }else if (vo2Max -49.6 <= 0) {
        runValue = 3;
        return runValue;
    }else
        runValue = 4;
        return runValue;
    }

// distance values to be given in KM
void metricsToImprove(double vo2Max, regressionResult a, double distance, double time, double heartRate, int* vo2MaxPos, int* runSPeed, int* runLength) {
    // determine what user needs to be told about various metrics


    double speed;
    speed = distance/time;

    // determine whether user ran fast enough
    if (speed < 9.1 ) {
        *runSPeed = 1;
    } else if (speed < 13.1) {
        *runSPeed = 2;
    }
    // TODO fix me so i am assigned the proper number
    // determine whether user ran far enough
    if (time*11.1 < distance+time) {
        *runLength = 0;
    } else if (time*11.1 > distance+time) {
        *runLength = 1;
    } else if (time*11.1 > distance-time) {
        *runLength = 0;
    } else if (time*11.1 < distance-time) {
        *runLength = 2;
    }

   // determine where vo2Max is relative to the average
    if (a.slope * heartRate + a.intercept > vo2Max) {
        *vo2MaxPos = 2;
    } else if (a.slope * heartRate + a.intercept <= vo2Max) {
        *vo2MaxPos = 1;
    }

}



void print(int runValue, double distance, double time, double heartRate, double vo2Max) {
    // TODO finish writing out the text output
    printf("************************************************************\n");
    printf("**                   Data on Your run:                    **\n");
    printf("**                                                        **\n");
    printf("**                   distance:   %.2lf                    **\n", distance);
    printf("**                   time:       %.2lf                    **\n", time);
    printf("**                   heart rate: %.2lf                    **\n", heartRate);
    printf("**                   vo2max:     %.2lf                    **\n", vo2Max);
    printf("**                                                        **\n"); //
    switch (runValue) {
        case 0:
            printf("**              you had an overall bad run                **\n");
            break;
        case 1:
            printf("**              you had an overall ok run                 **\n");
            break;
        case 2:
            printf("**              you had an overall good run               **\n");
            break;
        case 3:
            printf("**              you had an overall excellent run          **\n");
            break;
        case 4:
            printf("**              you had an overall perfect run            **\n");
            break;
    }
    printf("**                                                        **\n");
    printf("************************************************************\n");
    // runValue at 4 considered to be perfect so no improvements would be needed in that case
    if ( runValue == 4) {
        return;
    }






}








