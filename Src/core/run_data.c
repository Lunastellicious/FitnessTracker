//
// Created by lunas on 05-11-2025.
//


#include "../include/run_data.h"
#include <stdio.h>
#include <stdlib.h>

// defines constants
#define TRUE 1
#define conversionRate 1
#define MStoKMT 3.6


// functions
double stepsToDistance(int stepCount);
double generateDistance();
void generateElevation(double *elevation);
double generateTempo(int time, double distance);
void runData(int distanceStepBool, int stepCount);


int main() {
    for (int i =0; i < 10; i++){
    runData(500, 0);
}
    return 0;
}


// runs the other functions
// possibly return in from a pointer to a struct
void runData(int distanceStepBool, int stepCount) {
    double distance;
    double elevation[] = {0, 0};
    int time = 50;
    double test = 0;
    double test1 = 0;


    if (distanceStepBool == TRUE) {
        distance = stepsToDistance(stepCount);
    }
    else {
        distance = generateDistance();
    }
    // generateElevation(elevation);
    test1 = generateTempo(time, distance);
    test = distance;
    printf("distance = %lf tempo = %lf", test, test1);



}
// creates distance from an amount of steps
double stepsToDistance(int stepCount) {
    double distance;

    distance = stepCount*conversionRate;

    return distance;
}

// randomly generates a distance in Km
double generateDistance() {
    double distance;
    int max = 2000;
    int min = 0;

    distance = rand() % (max - min + 1) + min;

    return distance;
}

// generates tempo based off a time in seconds and a distance in M
// (needs to account for distance currently being kM and time being minutes or seconds)
double generateTempo(int time, double distance) {
    double tempo = 0;

    tempo=distance/time;
    tempo = tempo*MStoKMT;
    return tempo;
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
 return 1;
}





