//
// Created by lunas on 05-11-2025.
//

#include "../include/run_data.h"
#include <stdio.h>
#include <stdlib.h>


// unrealistisc number (vækstrate)
const int zone1Rate = 1;
const int zone2Rate = 2;
const int zone3Rate = 3;
const int zone4Rate = 4;
const int zone5Rate = 5;
const int anerobGR4 = zone4Rate * 2;
const int anerobGR5 = zone5Rate * 2;

const int scoreToTime = 2;


struct StructDeclaration {
    double time[5];
    int zone[5];
};

struct StructDeclaration structVariableName;

double calculateScore(double Time, int zone);

double calculateRestitution(struct StructDeclaration test);

int main() {
    double test = 0;

    for (int i = 0; i < 5; i++) {
        structVariableName.time[i] = i;
        structVariableName.zone[i] = i;
    }

    test = calculateRestitution(structVariableName);
    printf("Restitution is: %lf", test);
    return 0;
}


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
