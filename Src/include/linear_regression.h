//
// Created by lunas on 24-11-2025.
//

#ifndef FITNESSTRACKER_LINEAR_REGRESSION_H
#define FITNESSTRACKER_LINEAR_REGRESSION_H

typedef struct {
    double age[1000];
    double heightCm[1000];
    double weightKg[1000];
    double restingHeartRate[1000];
    double maxHeartRate[1000];
    double Vo2Max[1000];
    double cumulativeHits[1000];
    double cumulativeRuns[1000];
    double trainingHoursPerWeek[1000];
} dataLoad;

typedef struct
{
    double* x; //input data (datasets)
    double* VO2max; //output data  (VO2max)
    int size; //number of datapoints
    char* name; //description (input data)
    double weight; //trained weight (hældningskoefficient)
    double bias; //trained bias (skæring med y-aksen)

    //training/test split
    int train_size; //80%
    double* x_train;
    double* VO2max_train;
    int test_size; //20%
    double* x_test;
    double* VO2max_test;
} dataSet;

int machineLearning ();

#endif //FITNESSTRACKER_LINEAR_REGRESSION_H