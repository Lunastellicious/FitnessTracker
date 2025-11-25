//
// Created by lunas on 24-11-2025.
//

#include "../include/linear_regression.h"
#include <stdlib.h>
#include <stdio.h>

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


void split_datasets(dataSet* data, dataSet* dataSets, double train_ratio);
void split_datasettester(dataSet* data, double train_ratio); //tester til et dataset
static double* predict(dataSet* data);

int machineLearning ()
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
    double trainingHours_x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double VO2_trainingHours[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    dataSet trainingHours_data = {
        .x = trainingHours_x,
        .VO2max = VO2_trainingHours,
        .size = 10,
        .name = "training hours vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //array med alle datasets
    dataSet dataSets [] = {age_data, weight_data, restingHeartRate_data, maxHeartRate_data, cumulativeHits_data, cumulativeRuns_data, trainingHours_data};
    int num_dataSets = 7;

    //tester split
    //TODO: free mallocs
    //split_datasets(&dataSets, dataSets, 0.8);
    split_datasettester(&trainingHours_data, 0.8);

    printf("training data: \n");
    for (int i = 0; i < trainingHours_data.train_size; i++)
    {
        printf("%1.lf %1.lf \n ", trainingHours_data.x_train[i], trainingHours_data.VO2max_train[i]); //train data
    }

    printf("test data: \n");
    for (int i = 0; i < trainingHours_data.test_size; i++)
    {
        printf("%1.lf %1.lf \n ", trainingHours_data.x_test[i], trainingHours_data.VO2max_test[i]); //test data
    }

    //tester predict
    trainingHours_data.weight = 2.0;
    trainingHours_data.bias = 1;

    double* predictions = predict(&trainingHours_data);

    // Prints
    printf("Testing predict function:\n");
    printf("Formula: y = %.1f * x + %.1f\n\n",
           trainingHours_data.weight, trainingHours_data.bias);

    for (int i = 0; i < trainingHours_data.train_size; i++) {
        printf("X = %.1lf -> Predicted Y = %.1lf (Expected: %.1f)\n",
               trainingHours_data.x_train[i],
               predictions[i],
               2.0 * trainingHours_data.x_train[i] + 1.0);
    }

    free(predictions); //frigøre data igen


    return 0;


    // Frigør hukommelse når du er færdig!
}

//// FUNCTIONS

void split_datasettester(dataSet* data, double train_ratio) {
    // Beregner størrelser
    data->train_size = (int)(data->size * train_ratio);
    data->test_size = data->size - data->train_size;

    // Laver hukommelse til training data
    data->x_train = (double*)malloc(data->train_size * sizeof(double));
    data->VO2max_train = (double*)malloc(data->train_size * sizeof(double));

    // Laver hukommelse til test data
    data->x_test = (double*)malloc(data->test_size * sizeof(double));
    data->VO2max_test = (double*)malloc(data->test_size * sizeof(double));

    // Kopiere data til training data (80%)
    for (int i = 0; i < data->train_size; i++) {
        data->x_train[i] = data->x[i];
        data->VO2max_train[i] = data->VO2max[i];
    }

    // Kopiere data til test data (20%)
    for (int i = 0; i < data->test_size; i++) {
        data->x_test[i] = data->x[data->train_size + i];
        data->VO2max_test[i] = data->VO2max[data->train_size + i];
    }
}

void split_datasets(dataSet* data, dataSet* dataSets, double train_ratio)
{
    //splitter datasets op i 2 dele
    for (int data_size = 0; data_size < (sizeof(dataSets) / sizeof(dataSet)); data_size++)
    {
        // Beregner størrelser
        data->train_size = (int)(data->size * train_ratio);
        data->test_size = data->size - data->train_size;

        // Laver hukommelse til training data
        data->x_train = (double*)malloc(data->train_size * sizeof(double));
        data->VO2max_train = (double*)malloc(data->train_size * sizeof(double));

        // Laver hukommelse til test data
        data->x_test = (double*)malloc(data->test_size * sizeof(double));
        data->VO2max_test = (double*)malloc(data->test_size * sizeof(double));

        // Kopiere data til training data (80%)
        for (int i = 0; i < data->train_size; i++) {
            data->x_train[i] = data->x[i];
            data->VO2max_train[i] = data->VO2max[i];
        }

        // Kopiere data til test data (20%)
        for (int i = 0; i < data->test_size; i++) {
            data->x_test[i] = data->x[data->train_size + i];
            data->VO2max_test[i] = data->VO2max[data->train_size + i];
        }
    }
}

static double* predict(dataSet* data) {
    double* y_predicted = (double*)malloc(data->train_size * sizeof(double));
    for (int i = 0; i < data->train_size; i++) {
        y_predicted[i] = data->weight * data->x_train[i] + data->bias;
    }
    return y_predicted;
}


//TODO: predict function
