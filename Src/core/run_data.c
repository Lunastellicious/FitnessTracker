#include "../include/run_data.h"
#include "../include/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
//// ---------- CONST ----------

const int ACTIVEBPM_MIN = 115;
const int ACTIVEBPM_MAX = 195;

#define TRUE 1
// varies heavily based on an individuals height
const double conversionStepsPrMeter = 1.3;
// given in Km/t
const double averageHumanRunSPeed = 11;
const double MStoKMT = 3.6;

/*
const int zone1Rate = 1;
const int zone2Rate = 2;
const int zone3Rate = 3;
const int zone4Rate = 4;
const int zone5Rate = 5;
const int anerobGR4 = zone4Rate * 2;
const int anerobGR5 = zone5Rate * 2;
*/
// const int scoreToTime = 2;


//STRUCTS
typedef struct heartRateZone
{
    int MIN_BPM;
    int MAX_BPM;
    const char *name;
    const char *description;
} heartRateZone;




//Heart rate zones based on LTHR
/*
struct heartRateZone Zones[] = {
    {115, 136,  "Zone 1 (W)", "Warm up"},
    {137, 151, "Zone 2 (M)", "Marathon pace"},
    {152, 165, "Zone 3 (T)", "Lactate threshold pace"},
    {166, 174, "Zone 4 (AN)", "Anaerobic sprint"},
    {175, 190, "Zone 5 (I)", "High intensity interval training"}
}; */


//// ---------- PROTOTYPE FUNCTIONS ----------

double runDuration (int minMinutes, int maxMinutes);
void printRunDuration(double runTime);
int generateRunDurations();


double stepsToDistance(int stepCount);
double generateDistance(double runTime);
// void generateElevation(double *elevation);
double generateTempo(int time, double distance);
double distanceToRunTime(double runDistance);
void generateHRData (int* hrAvg, int* hrMax,int* hrRest);

//void kadencePerMinut(int steps[], int minute);
//double kadence(int sumSteps, int minut);



//// ---------- MAIN ----------

/* runData should not have a main as it is not the main executable
 *
int main (void)
{

    printRunDuration(runDuration(30, 50));
    generateHRData(runDuration(30, 50));

    //generateRunDurations();

    return 0;
}
*/

//// ---------- FUNCTIONS ----------



// main function that should be called
void runData(int min, int max, Database *current) {
    //given in seconds
    double runTime = 0;
    // given in Km
    double runDistance = 0;
    // given in Minutes
    double zoneTimes[5] = {0,0,0,0,0};
    int hrAvg = 0, hrRest = 0, hrMax = 0;

    // values currently not being calculated that will be in the future
    double restitutionTime = 0;
    double aerobScore = 0;
    double anerobScore = 0;



    runTime = runDuration(min, max);
    runDistance = generateDistance(runTime);

        //runDistance = stepsToDistance(stepcount);
        //runTime = distanceToRunTime(runDistance);

    // printRunDuration(runTime); option to write time of run to console
    generateHRData(&hrAvg, &hrMax, &hrRest);

    //sends data to struct
    set_distance(current, runDistance);
    set_duration(current, runTime);
    set_HRaverage(current, hrAvg);
    set_HRrest(current, hrRest);
    set_HRmax(current, hrMax);




}




// creates distance from an amount of steps
double stepsToDistance(int stepCount) {
    double distance;

    distance = stepCount*conversionStepsPrMeter;
    return distance;
}
// creates a run time from the given distance
double distanceToRunTime(double runDistance) {
    int runTime = 0;

    runTime = runDistance/(averageHumanRunSPeed/MStoKMT);
    return runTime;
}

// randomly generates a distance for the run based off the time of the run
double generateDistance(double runTime) {
    double distance = (averageHumanRunSPeed)*runTime;
    
    return distance;
}

// generates tempo based off a time in seconds and a distance in M
// needs distance in M
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
void generateHRData (int* hrAvg, int* hrMax,int* hrRest) {

    int variation1 = 0, varaiation2 = 0;
    // csv HRavg average = 155
    // csv HRmax avreage = 171
    // HRmin for 26-35 women 60-64 used 62

    variation1 = (rand() % (-5 - 5 + 1));
    // higher varation as max heartrate varies further than minimum
    varaiation2 = (rand() % (-10 - 10 + 1));

    *hrRest = 62 + variation1;
    *hrMax = 171 + varaiation2;
    *hrAvg = (*hrRest+*hrMax)/2;
}


/* To be continued...
void kadencePerMinut(int steps[], int minute) {
    for (int i = 0; i < minute; i++) {
        printf("Your kadence for the minute: %d er %d steps pr. min\n", i+1, steps[i]);
    }

}
// kadence for hele løbet
double kadence(int sumSteps, int minut) {
    return (double) sumSteps/minut;
}
*/

//// ---------- unused code ----------

/*

 // restituition time function based off anerob and aerob needs changing befdore implementation

struct StructDeclaration {
    double time[5];
    int zone[5];
};


double calculateRestitution(struct StructDeclaration test) {
    // recieve input
    double restitutionTime;
    double score;

    // time * zone rate? iterate and add up for all zones
    for (int i = 0; i < 5; i++) {
        score = calculateScore(test.time[i], test.zone[i]);
    }


    // use score to calculate restitution time

    restitutionTime = score * scoreToTime;

    return restitutionTime;
}

double calculateScore(double Time, int zone) {
    double score;

    switch (zone) {
    case 1:
        score += Time * zone1Rate;
        break;
    case 2:
        score += Time * zone2Rate;
        break;
    case 3:
        score += Time * zone3Rate;
        break;
    case 4:
        score += Time * anerobGR4;
        break;
    case 5:
        score += Time * anerobGR5;
        break;
    default:
        printf("Invalid zone\n");
        break;
    }

    return score;
}

 // was used for testing purposes
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

// old version of HRdata function
/*
int generateHRData (double totalSeconds, double *zoneTimes)
{

    int totalMinutes = totalSeconds / 60;

    //Rand interval
    double Z1_time = (rand() % (20 - 5 + 1) + 5);
    double Z2_time = (rand() % (50 - 5 + 1) + 5);
    double Z3_time = (rand() % (10 - 5 + 1) + 5);
    double Z4_time = (rand() % (10 - 5 + 1) + 5);
    double Z5_time = (rand() % (10 - 5 + 1) + 5);

    double distributionSum = Z1_time + Z2_time + Z3_time + Z4_time + Z5_time;

    // should not print to console during normal operations
    // printf("distribution %.02lf \n " , distributionSum);

    //distribution in minutes
    /*
    double const Z1 = totalMinutes * (Z1_time / distributionSum);
    double const Z2 = totalMinutes * (Z2_time / distributionSum);

    double const Z3 = totalMinutes * (Z3_time / distributionSum); //lactate threshold

    double const Z4 = totalMinutes * (Z4_time / distributionSum);
    double const Z5 = totalMinutes * (Z5_time / distributionSum);


zoneTimes[0] = totalMinutes * (Z1_time / distributionSum);
zoneTimes[1] = totalMinutes * (Z2_time / distributionSum);

zoneTimes[2] = totalMinutes * (Z3_time / distributionSum); //lactate threshold

zoneTimes[3] = totalMinutes * (Z4_time / distributionSum);
zoneTimes[4] = totalMinutes * (Z5_time / distributionSum);

// should not print to console during normal operations

printf("Z1 %.2lf \n", zoneTimes[0]);
printf("Z2 %.2lf \n", zoneTimes[1]);
printf("Z3 %.2lf \n", zoneTimes[2]);
printf("Z4 %.2lf \n", zoneTimes[3]);
printf("Z4 %.2lf \n", zoneTimes[4]);

}

*/