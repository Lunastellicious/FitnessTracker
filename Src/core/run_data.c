//
// Created by lunas on 05-11-2025.
//

#define TRUE 1
#define conversionRate 0

#include "../include/run_data.h"
#include <stdio.h>
#include <stdlib.h>

double stepsToDistance(int stepCount);
double generateDistance();
void generateElevation(double *elevation);

// possibly return in from a pointer to a struct
void runData(int distanceStepBool, int stepCount) {
    double distance;
    double elevation[] = {0, 0};

    if (distanceStepBool == TRUE) {
        distance = stepsToDistance(stepCount);
    }
    else {
        distance = generateDistance();
    }
    generateElevation(elevation);

}

double stepsToDistance(int stepCount) {
    double distance;

    distance = stepCount*conversionRate;

    return distance;
}

double generateDistance() {
    double distance;
    int max = 20;
    int min = 0;

    distance = rand() % (max - min + 1) + min;

    return distance;
}
/*

 function remains if deemed to be needed later

void generateElevation(double *elevation) {
    int max = 20;
    int min = 0;

    // rand eleveation for route minimum being negative value at [0] and max being positive at [1]


}
*/



int pulse_data (void)
{

}





