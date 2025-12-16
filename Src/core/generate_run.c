
// This file generates a run for a user
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// CONSTANTS
const int VO2MaximumValue = 45;
const int VO2MinimumValue = 38;

const double AVERAGE_HUMAN_RUN_SPEED_KMH = 11.0;

//Pace bounds



// PROTOTYPES
int generateVO2MAX(void);
int runDurationSeconds(int minMinutes, int maxMinutes);
void printRunDurationHMS(int total_seconds);
double runTimeMinutes(int total_seconds);
double generateDistanceKm(int total_seconds, double speed_kmh);
double generatePaceMinPerKm(double run_minutes, double distance_km);


int generateMain(void)
{
    // Seed RNG once
    srand((unsigned)time(NULL));

    // Generate run duration
    int total_seconds = runDurationSeconds(15, 60);
    printRunDurationHMS(total_seconds);

    // Convert to minutes
    double total_minutes = runTimeMinutes(total_seconds);

    // Distance using average human running speed
    double distance_km = generateDistanceKm(total_seconds, AVERAGE_HUMAN_RUN_SPEED_KMH);

    // Pace (min/km)
    double pace_min_per_km = generatePaceMinPerKm(total_minutes, distance_km);

    // VO2MAX random example (optional)
    int vo2max = generateVO2MAX();

    printf("Run total time: %d seconds (%.2f minutes)\n", total_seconds, total_minutes);
    printf("Distance: %.2f km at %.2f km/h\n", distance_km, AVERAGE_HUMAN_RUN_SPEED_KMH);
    printf("Average pace: %.2f min/km\n", pace_min_per_km);
    printf("Random VO2MAX: %d\n", vo2max);

    return 0;
}

int generateVO2MAX(void)
{
    // Uniform int in [VO2MinimumValue, VO2MaximumValue]
    return VO2MinimumValue + rand() % (VO2MaximumValue - VO2MinimumValue + 1);
}

// Returns total duration in seconds
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
        // Avoid division by zero; return 0 or NAN depending on your preference
        return 0.0;
    }
    return run_minutes / distance_km;
}



