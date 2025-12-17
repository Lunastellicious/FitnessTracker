
// This file generates a run for a user
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/data.h"

////CONSTANTS
const int VO2MaximumValue = 45;
const int VO2MinimumValue = 38;

const double AVERAGE_HUMAN_RUN_SPEED_KMH = 11.0; // km/h

//// PROTOTYPES
int generateVO2MAX(void);
int runDurationSeconds(int minMinutes, int maxMinutes);
void printRunDurationHMS(int total_seconds);
double runTimeMinutes(int total_seconds);
double generateDistanceKm(int total_seconds, double speed_kmh);
double generatePaceMinPerKm(double run_minutes, double distance_km);
int generateHRData (int* hrMin, int* hrAvg, int* hrMax); //TODO: make HR work

// Simple pace helper (min/km) directly from seconds + km
double computePace(int total_seconds, double distance_km);

// Training Effect functions (simple linear models)
double computeAerobicTE(double pace_min_per_km, int total_seconds);
double computeAnaerobicTE(double pace_min_per_km, int total_seconds);
double computeTotalTE(double aerobic_te, double anaerobic_te);
double computeRecovery(double totalTE);

////MAIN
int generateMain(Database* current)
{
    // Seed RNG once
    srand((unsigned)time(NULL));

    // Generate run duration
    int total_seconds = runDurationSeconds(15, 60);
    printRunDurationHMS(total_seconds);

    // Convert to minutes
    current->duration = runTimeMinutes(total_seconds);

    // Distance
    current->distance = generateDistanceKm(total_seconds, AVERAGE_HUMAN_RUN_SPEED_KMH);

    // Pace (min/km)
    current->pace = generatePaceMinPerKm(current->duration, current->distance);

    // VO2MAX  example
    current->VO2max = (double) generateVO2MAX();

    int hrMin = 0, hrAvg =0, hrMax = 0;

    printf("Run total time: %d seconds (%.2f minutes)\n", total_seconds, current->duration);
    printf("Distance: %.2f km at %.2f km/h\n", current->distance, AVERAGE_HUMAN_RUN_SPEED_KMH);
    printf("Average pace: %.2f min/km\n", current->pace);
    printf("Random VO2MAX: %d\n", current->VO2max);
    //HR
    int hrMin = 0, hrAvg =0, hrMax = 0;


    //TE and recovery based on the generated run
    current->aerobic = computeAerobicTE(current->pace, total_seconds);
    current->anaerobic = computeAnaerobicTE(current->pace, total_seconds);
    current->totalTE = computeTotalTE(current->aerobic, current->anaerobic);
    current->recovery = computeRecovery(current->totalTE);

    printf("Aerobic TE: %.2f\n", current->aerobic);
    printf("Anaerobic TE: %.2f\n", current->anaerobic);
    printf("Total TE: %.2f\n", current->totalTE);
    printf("Recovery: %.1f hours\n", current->recovery);

    return 0;
}

////Functions

int generateVO2MAX(void)
{
    return VO2MinimumValue + rand() % (VO2MaximumValue - VO2MinimumValue + 1);
}

int runDurationSeconds(int minMinutes, int maxMinutes)
{
    int minutes = minMinutes + rand() % (maxMinutes - minMinutes + 1);
    int seconds = rand() % 60;
    return minutes * 60 + seconds;
}

void printRunDurationHMS(int total_seconds)
{
    int hours   = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;
    printf("Run duration (H:M:S): %02d:%02d:%02d\n", hours, minutes, seconds);
}

double runTimeMinutes(int total_seconds)
{
    return total_seconds / 60.0;
}

double generateDistanceKm(int total_seconds, double speed_kmh)
{
    // distance = speed(km/h) * time(h)
    return speed_kmh * (total_seconds / 3600.0);
}

double generatePaceMinPerKm(double run_minutes, double distance_km)
{
    if (distance_km <= 0.0) {

        return 0.0;
    }
    return run_minutes / distance_km; // min/km
}

int generateHRData (int* hrMin, int* hrAvg, int* hrMax)
{
    int variation1 = 0, variation2 = 0;

    // csv hrAVG average = 155
    // csv hrMAX average = 171
    // sourced hrMIn average for 20s woman 60-64: 62 used

    variation1= (rand() % -5 - 5 +1);
    variation2= (rand() % -10 - 10 +1);

    *hrMin = 62+variation1;
    *hrMax = 171+variation2;
    * hrAvg = (*hrMin+*hrMax)/2;
}


double computePace(int total_seconds, double distance_km)
{
    double minutes = total_seconds / 60.0;
    if (distance_km <= 0.0) return 0.0;
    return minutes / distance_km; // min/km
}


double computeAerobicTE(double pace, int total_seconds)
{
    double minutes = total_seconds / 60.0;

    double te = (7.0 - pace) * 0.8 + (minutes / 60.0) * 2.0;
    if (te < 0.0) te = 0.0;
    if (te > 5.0) te = 5.0;
    return te;
}

double computeAnaerobicTE(double pace, int total_seconds)
{
    double minutes = total_seconds / 60.0;
    double te = (6.0 - pace) * 1.2 + (minutes / 30.0);
    if (te < 0.0) te = 0.0;
    if (te > 5.0) te = 5.0;
    return te;
}

double computeTotalTE(double aerobic, double anaerobic)
{
    double total = aerobic + anaerobic;
    if (total < 0.0) total = 0.0;
    if (total > 10.0) total = 10.0;
    return total;
}

double computeRecovery(double totalTE)
{
    return 12.0 + totalTE * 6.0; // base + factor
}






