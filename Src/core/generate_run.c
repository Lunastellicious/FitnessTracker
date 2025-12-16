
// This file generates a run for a user
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Simple pace helper (min/km) directly from seconds + km
double computePace(int total_seconds, double distance_km);

// Training Effect functions (simple linear models)
double computeAerobicTE(double pace_min_per_km, int total_seconds);
double computeAnaerobicTE(double pace_min_per_km, int total_seconds);
double computeTotalTE(double aerobic_te, double anaerobic_te);
double computeRecovery(double totalTE);

////MAIN
int generateMain(void)
{
    // Seed RNG once
    srand((unsigned)time(NULL));

    // Generate run duration
    int total_seconds = runDurationSeconds(15, 60);
    printRunDurationHMS(total_seconds);

    // Convert to minutes
    double total_minutes = runTimeMinutes(total_seconds);

    // Distance
    double distance_km = generateDistanceKm(total_seconds, AVERAGE_HUMAN_RUN_SPEED_KMH);

    // Pace (min/km)
    double pace_min_per_km = generatePaceMinPerKm(total_minutes, distance_km);

    // VO2MAX  example
    int vo2max = generateVO2MAX();

    printf("Run total time: %d seconds (%.2f minutes)\n", total_seconds, total_minutes);
    printf("Distance: %.2f km at %.2f km/h\n", distance_km, AVERAGE_HUMAN_RUN_SPEED_KMH);
    printf("Average pace: %.2f min/km\n", pace_min_per_km);
    printf("Random VO2MAX: %d\n", vo2max);

    //TE and recovery based on the generated run
    double aerobic   = computeAerobicTE(pace_min_per_km, total_seconds);
    double anaerobic = computeAnaerobicTE(pace_min_per_km, total_seconds);
    double totalTE   = computeTotalTE(aerobic, anaerobic);
    double recovery  = computeRecovery(totalTE);

    printf("Aerobic TE: %.2f\n", aerobic);
    printf("Anaerobic TE: %.2f\n", anaerobic);
    printf("Total TE: %.2f\n", totalTE);
    printf("Recovery: %.1f hours\n", recovery);

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






