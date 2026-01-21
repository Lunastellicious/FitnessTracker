
// This file generates a run for a user
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/data.h"

////CONSTANTS
const int VO2MaximumValue = 45;
const int VO2MinimumValue = 38;

const double AVERAGE_HUMAN_RUN_SPEED_KMH = 11.0; // km/h

//avg from dataset
const double RESTING_HEARTRATE = 62;
const double AVERAGE_HEARTRATE = 145;
const double MAX_HEARTRATE = 170;


// TE
const double AEROBIC_BASE_PACE = 8.0; // Reference-pace
const double AEROBIC_PACE_FACTOR = 0.8; // Vægtning af tempo
const double AEROBIC_TIME_FACTOR = 3.0; // TE-point pr. time (via minutes/60)
const double ANAEROBIC_BASE_PACE = 6.0;
const double ANAEROBIC_PACE_FACTOR = 1.2; //højere tempo-følsomhed
const double ANAEROBIC_TIME_DIVISOR = 30; //1.0 TE per 30 min (2.0/time)
const double MAX_TE = 5.0;
const double MIN_TE = 0.0;
const double MAX_TOTAL_TE = 10; //samlet TE

//Recovery
const double RECOVERY_BASE_HOURS = 6.0; //minimum restitution time
const double AEROBIC_RECOVERY_FACTOR = 4; //antal timer restitution pr. aerob TE point
const double ANAEROBIC_RECOVERY_FACTOR = 8; //antal timer restitution pr. anaerob TE point


//// PROTOTYPES
double generateVO2MAX(void);
int runDurationSeconds(int minMinutes, int maxMinutes);
void printRunDurationHMS(int total_seconds);
double runTimeMinutes(int total_seconds);
double generateDistanceKm(int total_seconds, double speed_kmh);
double generatePaceMinPerKm(double run_minutes, double distance_km);
int generateHRData(Database* current); //TODO: make HR work

// Simple pace helper (min/km) directly from seconds + km
double computePace(int total_seconds, double distance_km);

// Training Effect functions (simple linear models)
double computeAerobicTE(double pace_min_per_km, int total_seconds);
double computeAnaerobicTE(double pace_min_per_km, int total_seconds);
double computeTotalTE(double aerobic_te, double anaerobic_te);
double computeRecovery(double aerobic, double anaerobic);

////MAIN
int generateMain(Database *current)
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
    current->VO2max = generateVO2MAX();

    generateHRData(current);

    printf("Run total time: %d seconds (%.2f minutes)\n", total_seconds, current->duration);
    printf("Distance: %.2f km at %.2f km/h\n", current->distance, AVERAGE_HUMAN_RUN_SPEED_KMH);
    printf("Average pace: %.2f min/km\n", current->pace);
    printf("Random VO2MAX: %lf\n", current->VO2max);
    //HR
    //int hrMin = 0, hrAvg =0, hrMax = 0;


    //TE and recovery based on the generated run
    current->aerobic = computeAerobicTE(current->pace, total_seconds);
    current->anaerobic = computeAnaerobicTE(current->pace, total_seconds);
    current->totalTE = computeTotalTE(current->aerobic, current->anaerobic);
    current->recovery = computeRecovery(current->aerobic, current->anaerobic);

    printf("Aerobic TE: %.2f\n", current->aerobic);
    printf("Anaerobic TE: %.2f\n", current->anaerobic);
    printf("Total TE: %.2f\n", current->totalTE);
    printf("Recovery: %.1f hours\n", current->recovery);

    return 0;
}

////Functions

double generateVO2MAX(void)
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
    return speed_kmh*((double)(rand() % 100)/100 + 0.3) * (total_seconds / 3600.0);
}

double generatePaceMinPerKm(double run_minutes, double distance_km)
{
    if (distance_km <= 0.0) {

        return 0.0;
    }
    return run_minutes / distance_km; // min/km
}

/*int generateHRData (Database *current)
{
    int variation1 = 0, variation2 = 0;

    // csv hrAVG average = 155
    // csv hrMAX average = 171
    // sourced hrMIn average for 20s woman 60-64: 62 used

    variation1= (rand() % -5 - 5 +1);
    variation2= (rand() % -10 - 10 +1);

    current->HRrest = 62+variation1;
    current->HRmax = 171+variation2;
    current->HRaverage = (current->HRrest+current->HRmax)/2;
}*/


int generateHRData (Database *current)
{
    int hrRest = RESTING_HEARTRATE + rand() % 6; // 60-65
    int hrMax = MAX_HEARTRATE + rand() % 21; //165-185
    int hrAvg = AVERAGE_HEARTRATE + rand() % 21; //145-165

    current->HRrest = hrRest;
    current->HRmax = hrMax;
    current->HRaverage = hrAvg;

    printf("Max Heart Rate: %d\n", current->HRmax);

    return 0;

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

    double aerobictTE = (AEROBIC_BASE_PACE - pace) * AEROBIC_PACE_FACTOR + (minutes / 60.0) * AEROBIC_TIME_FACTOR;
    if (aerobictTE < MIN_TE) aerobictTE = MIN_TE;
    if (aerobictTE > MAX_TE) aerobictTE = MAX_TE;
    return aerobictTE;
}

double computeAnaerobicTE(double pace, int total_seconds)
{
    double minutes = total_seconds / 60.0;

    double anaerobicTE = (ANAEROBIC_BASE_PACE - pace) * AEROBIC_PACE_FACTOR + (minutes / ANAEROBIC_TIME_DIVISOR); //
    if (anaerobicTE < MIN_TE) anaerobicTE = MIN_TE;
    if (anaerobicTE > MAX_TE) anaerobicTE = MAX_TE;
    return anaerobicTE;
}

double computeTotalTE(double aerobic, double anaerobic)
{
    double total = aerobic + anaerobic;

    if (total < MIN_TE) total = MIN_TE;
    if (total > MAX_TOTAL_TE) total = MAX_TOTAL_TE;
    return total;
}

double computeRecovery(double aerobic, double anaerobic)
{
    double recoveryHours = RECOVERY_BASE_HOURS + (aerobic * 4) + (anaerobic * 8);
    return recoveryHours;
}






