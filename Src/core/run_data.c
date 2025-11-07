//
// Created by lunas on 05-11-2025.
//

#include "../include/run_data.h"
#include <stdio.h>
#include <stdlib.h>


#define zone1Rate 1
#define zone2Rate 2
#define zone3Rate 3
#define zone4Rate 4
#define zone5Rate 5
#define scoreToTime 2

struct StructDeclaration{
    double time[5];
    int zone[5];
};

struct StructDeclaration structVariableName;


double calculateScore(double Time,int zone);


double calculateRestitution(struct StructDeclaration test) {
    // recieve input
    double restitutionTime;
    double score;

    // time * zone rate? iterate and add up for all zones
    for (int i = 0; i < 5; i++) {
        calculateScore(test.time[i],test.zone[i]);
    }


    // use score to calculate restitution time

    restitutionTime = score*scoreToTime;

    return restitutionTime;
}

double calculateScore(double Time,int zone) {
    double score;

    switch (zone) {
        case 1:
            score += Time*zone1Rate;
            break;
        case 2:
            score += Time*zone2Rate;
            break;
        case 3:
            score += Time*zone3Rate;
            break;
        case 4:
            score += Time*zone4Rate;
            score += Time*zone4Rate;
            break;
        case 5:
            score += Time*zone5Rate;
            score += Time*zone5Rate;
            break;
        default:
            printf("Invalid zone\n");
            break;

    }

    return score;
}

void Explain() {
    calculateRestitution(structVariableName);
    calculateRestitution(structName);
}
















int pulse_data (void)
{

}

