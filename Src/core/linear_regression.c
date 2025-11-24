//
// Created by lunas on 24-11-2025.
//

#include "../include/linear_regression.h"

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
    int test_size; //20%
} dataSet;

static double* predict (double inputs[], int size, double weight, double bias);
void split_dataset(dataSet* data, double train_ratio);

int main ()
{
    //age data
    double age_x[] = {};
    double VO2_age[] = {};
    dataSet age_data = {
        .x = age_x,
        .VO2max = VO2_age,
        .size = 1000,
        .name = "age vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //weight data
    double weight_x[] = {};
    double VO2_weight[] = {};
    dataSet weight_data = {
        .x = weight_x,
        .VO2max = VO2_weight,
        .size = 1000,
        .name = "weight vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //resting heart rate
    double restingHeartRate_x[] = {};
    double VO2_restingHeartRate[] = {};
    dataSet restingHeartRate_data = {
        .x = restingHeartRate_x,
        .VO2max = VO2_restingHeartRate,
        .size = 1000,
        .name = "resting heart rate vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //max heart rate
    double maxHeartRate_x[] = {};
    double VO2_maxHeartRate[] = {};
    dataSet maxHeartRate_data = {
        .x = maxHeartRate_x,
        .VO2max = VO2_maxHeartRate,
        .size = 1000,
        .name = "max heart rate vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //Cumulative hits TODO: definition
    double cumulativeHits_x[] = {};
    double VO2_cumulativeHits[] = {};
    dataSet cumulativeHits_data = {
        .x = cumulativeHits_x,
        .VO2max = VO2_cumulativeHits,
        .size = 1000,
        .name = "cumulative hits vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //Cumulative Runs TODO: definition
    double cumulativeRuns_x[] = {};
    double VO2_cumulativeRuns[] = {};
    dataSet cumulativeRuns_data = {
        .x = cumulativeRuns_x,
        .VO2max = VO2_cumulativeRuns,
        .size = 1000,
        .name = "cumulative runs vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //training hours
    double trainingHours_x[] = {};
    double VO2_trainingHours[] = {};
    dataSet trainingHours_data = {
        .x = trainingHours_x,
        .VO2max = VO2_trainingHours,
        .size = 1000,
        .name = "training hours vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //array med alle datasets
    dataSet dataSets [] = {age_data, weight_data, restingHeartRate_data, maxHeartRate_data, cumulativeHits_data, cumulativeRuns_data, trainingHours_data};
    int num_dataSets = 7;
    split_dataset(&age_data, 0.8);
}

//ændre input ved funktionskald

static double* predict (double inputs[], int size, double weight, double bias);

void split_dataset(dataSet* data, double data_ratio) { //splitter datasets op i 2 dele
    data->train_size = (int)(data->size * data_ratio);
    data->test_size = data->size - data->train_size;
}