#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>




// CONSTANTS
const int ACTIVEBPM_MIN = 115;
const int ACTIVEBPM_MAX = 195;


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


// PROTOTYPE FUNCTIONS
double runDuration (int minMinutes, int maxMinutes);
void printRunDuration(double runTime);
int generateRunDurations();
int generateHRData (double totalSeconds);


//MAIN
int main (void)
{

    //printRunDuration(runDuration(30, 50));
    double time = runDuration(30, 60);
    generateHRData(time);

    //generateRunDurations();

        return 0;
}


//FUNCTIONS

//generates run
double runDuration (int minMinutes, int maxMinutes) {
    srand(time(NULL)); //initializes for current time

    int minutes = minMinutes + (rand() % (maxMinutes - minMinutes + 1));
    int seconds = rand() % 60;

    int runTime = minutes * 60.0 + seconds;

    printf("%d \n", runTime);
    return runTime;
}

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

void printRunDuration (double runTime)
{
    //Converts runTime
    int total_seconds = (int)runTime;
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    printf("Run duration (H:M:S): %02d:%02d:%02d \n", hours, minutes, seconds);
}


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