#include "../include/recommends.h"
#include <stdio.h>
#include "../include/linear_regression.h"
#include <math.h>
#include <stdlib.h>
#include "../include/data.h"

void metricsToImprove(regressionResult* a, metrics* rec, Database* current);
void print(int runValue, regressionResult* a, metrics* rec, Database* current);
int evaluateRun(double vo2Max);

// distance values to be given in KM
void recommend(Database* current, regressionResult* a) {
    metrics rec;
    
    int runValue = 0; // determines the value of a run: 0 = bad: 1 = ok: 2 = good: 3 = excellent: 4 being perfect
    runValue = evaluateRun(current->VO2max);

    // TODO: call metrics to improve and call print
    metricsToImprove(a, &rec, current);
    print(runValue, a, &rec, current);

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
void metricsToImprove(regressionResult* a, metrics* rec, Database* current) {
    // determine what user needs to be told about various metrics


    double speed;
    speed = current->distance/(current->duration/60);

    // determine whether user ran fast enough
    if (speed < 9.1 ) {
        rec->runSPeed = 1;
    } else if (speed < 13.1) {
        rec->runSPeed = 2;
    }

    // determine whether user ran far enough 1 means above expected 2 means below expected
    if (11.1*current->duration > (11.1*current->duration)-2*current->duration) {
        rec->runLength = 1;
    } else if (11.1*current->duration < (11.1*current->duration)+2*current->duration) {
        rec->runLength = 2;
    }

   // determine where vo2Max is relative to the average
    if (a->slope * current->pace + a->intercept > current->VO2max) {
        rec->vo2MaxPos = 1;
    } else if (a->slope * current->pace + a->intercept <= current->VO2max) {
        rec->vo2MaxPos = 2;
    }

}



void print(int runValue, regressionResult* a, metrics* rec, Database* current) {
    // TODO finish writing out the text output
    printf("************************************************************\n");
    printf("**                   Data on Your run:                    **\n");
    printf("**                                                        **\n");
    printf("**                   distance:   %.2lf                    **\n", current->distance);
    printf("**                   time:       %.2lf                    **\n", current->duration);
    printf("**                   heart rate: %.2lf                    **\n", current->HRmax);
    printf("**                   vo2max:     %.2lf                    **\n", current->VO2max);
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
        default:
            printf("print function failed");
            exit(EXIT_FAILURE);
    }
    printf("**                                                        **\n");
    printf("************************************************************\n");
    // runValue at 4 considered to be perfect so no improvements would be needed in that case
    if ( runValue == 4) {
        return;
    }
    printf("\n\n");

    switch (rec->runSPeed) {
       case 1:
            printf("info: you ran at speed of %.2lf which is below the expected. suggest running faster on your next run: ideal speed between 9.1 km/h and 13.1 km/h \n", current->distance/(current->duration/60));
            break;
        case 2:
            printf("info: you ran at speed of %.2lf which is above the expected. suggest running slower on your next run: ideal speed between 9.1 km/h and 13.1 km/h \n", current->distance/(current->duration/60));
            break;
        default:
            printf("print function failed");
            exit((EXIT_FAILURE));
    }

    switch (rec->runLength) {
        case 1:
            printf("info: you ran farther than the average person for the recorded run duration: suggest lowering the distance of your run slightly \n");
            break;
        case 2:
            printf("info: you ran less than the average person for the recorded run duration: suggest increasing the distance of your run slightly \n");
        default:
            printf("print function failed");
            exit((EXIT_FAILURE));
    }

    switch ( (rec->vo2MaxPos)) {
        case 1:
            printf("Your vo2Max was found to be below average: average for the recoder heart rate %.2lf your vo2Max %.2lf\n", a->slope * current->pace + a->intercept, current->VO2max);
            break;
        case 2:
            printf("Your vo2Max was found to be above average: average for the recoder heart rate %.2lf your vo2Max %.2lf  which is good sign\n", a->slope * current->pace + a->intercept, current->VO2max);
            break;
        default:
            printf("print function failed");
            exit((EXIT_FAILURE));
    }

}








