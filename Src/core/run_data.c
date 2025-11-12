#include "../include/run_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>


//// ---------- CONST ----------

const int ACTIVEBPM_MIN = 115;
const int ACTIVEBPM_MAX = 195;

#define TRUE 1
const int conversionRate = 1;
const double MStoKMT = 3.6;


//STRUCTS
typedef struct heartRateZone
{
    int MIN_BPM;
    int MAX_BPM;
    const char *name;
    const char *description;
} heartRateZone;



//Heart rate zones based on LTHR
struct heartRateZone Zones[] = {
    {115, 136,  "Zone 1 (W)", "Warm up"},
    {137, 151, "Zone 2 (M)", "Marathon pace"},
    {152, 165, "Zone 3 (T)", "Lactate threshold pace"},
    {166, 174, "Zone 4 (AN)", "Anaerobic sprint"},
    {175, 190, "Zone 5 (I)", "High intensity interval training"}
};


//// ---------- PROTOTYPE FUNCTIONS ----------

double runDuration (int minMinutes, int maxMinutes);
void printRunDuration(double runTime);
int generateRunDurations();
int generateHRData (double totalSeconds);

double stepsToDistance(int stepCount);
double generateDistance();
void generateElevation(double *elevation);
double generateTempo(int time, double distance);
void runData(int distanceStepBool, int stepCount);

void kadencePerMinut(int steps[], int minute);
double kadence(int sumSteps, int minut);


//// ---------- MAIN ----------

int main (void)
{

    printRunDuration(runDuration(30, 50));
    generateHRData(runDuration(30, 50));

    //generateRunDurations();

    return 0;
}


//// ---------- FUNCTIONS ----------


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


//generates run
double runDuration (int minMinutes, int maxMinutes) {
    srand(time(NULL)); //initializes for current time

    int minutes = minMinutes + (rand() % (maxMinutes - minMinutes + 1));
    int seconds = rand() % 60;

    int runTime = minutes * 60.0 + seconds;

    printf("%d \n", runTime);
    return runTime;
}

//generates 5 runs with different durations (ascending)
int generateRunDurations()
{
    for (int i = 0 ; i <= 5 ; i++)
    {
        sleep(1);
        printf("Løb %d - ", i);
        double runTime = runDuration(25, 120);
        printRunDuration(runTime);
    }
    return 0;
}

//prints run in hour:min:seconds format
void printRunDuration (double runTime)
{
    //Converts runTime
    int total_seconds = (int)runTime;
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    printf("Run duration (H:M:S): %02d:%02d:%02d \n", hours, minutes, seconds);
}

//distributes run duration into zones
int generateHRData (double totalSeconds)
{

    int totalMinutes = totalSeconds / 60;

    //Rand interval
    double Z1_time = (rand() % (20 - 5 + 1) + 5);
    double Z2_time = (rand() % (50 - 5 + 1) + 5);
    double Z3_time = (rand() % (10 - 5 + 1) + 5);
    double Z4_time = (rand() % (10 - 5 + 1) + 5);
    double Z5_time = (rand() % (10 - 5 + 1) + 5);

    double distributionSum = Z1_time + Z2_time + Z3_time + Z4_time + Z5_time;

    printf("distribution %.02lf \n " , distributionSum);

    //distribution in minutes
    double const Z1 = totalMinutes * (Z1_time / distributionSum);
    double const Z2 = totalMinutes * (Z2_time / distributionSum);

    double const Z3 = totalMinutes * (Z3_time / distributionSum); //lactate threshold

    double const Z4 = totalMinutes * (Z4_time / distributionSum);
    double const Z5 = totalMinutes * (Z5_time / distributionSum);

    printf("Z1 %.2lf \n", Z1);
    printf("Z2 %.2lf \n", Z2);
    printf("Z3 %.2lf \n", Z3);
    printf("Z4 %.2lf \n", Z4);
    printf("Z4 %.2lf \n", Z5);
}


void kadencePerMinut(int steps[], int minute) {
    for (int i = 0; i < minute; i++) {
        printf("Your kadence for the minute: %d er %d steps pr. min\n", i+1, steps[i]);
    }

}
// kadence for hele løbet
double kadence(int sumSteps, int minut) {
    return (double) sumSteps/minut;
}