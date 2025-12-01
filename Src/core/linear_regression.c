//
// Created by lunas on 24-11-2025.
//

#include "../include/linear_regression.h"
#include <stdlib.h>
#include <stdio.h>

void split_datasets(dataSet* data, dataSet* dataSets, double train_ratio);
void split_datasettester(dataSet* data, double train_ratio); //tester til et dataset
static double* predict(dataSet* data);
static double cost(dataSet* data);
static double weightGrad(dataSet* data);
static double biasGrad(dataSet* data);
void testRegression(dataSet* date);
void testLoad(dataLoad test);

int machineLearning ()
{
    dataLoad dataSet1;
    FILE *fData;
    //open a file in read mode
    fData = fopen("sports_training_dataset.csv","r");

    if (fData == NULL) {
        printf("failed to load");
        exit(EXIT_FAILURE);
    }

    fscanf(fData, "%*[^\n]\n");

    for (int i = 0; i<1000; i++ ) {

        fscanf(fData, "%*[^,],");
        fscanf(fData, "%d,%d,%d,%d,%d,%lf,%d,%d,%d",
           &dataSet1.age[i],
           &dataSet1.heightCm[i],
           &dataSet1.weightKg[i],
           &dataSet1.restingHeartRate[i],
           &dataSet1.maxHeartRate[i],
           &dataSet1.Vo2Max[i],
           &dataSet1.cumulativeHits[i],
           &dataSet1.cumulativeRuns[i],
           &dataSet1.trainingHoursPerWeek[i]);
        fscanf(fData, "%*[^\n]\n");

    }
    fclose(fData);


    //age data
    dataSet age_data = {
        .x = dataSet1.age,
        .VO2max = dataSet1.Vo2Max,
        .size = sizeof(age_data.x),
        .name = "age vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //weight data
    double weight_x[] = {};
    double VO2_weight[] = {};
    dataSet weight_data = {
        .x = dataSet1.weightKg,
        .VO2max = dataSet1.Vo2Max,
        .size = sizeof(weight_data.x),
        .name = "weight vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //resting heart rate
    dataSet restingHeartRate_data = {
        .x = dataSet1.restingHeartRate,
        .VO2max = dataSet1.Vo2Max,
        .size = sizeof(restingHeartRate_data.x),
        .name = "resting heart rate vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //max heart rate
    dataSet maxHeartRate_data = {
        .x = dataSet1.maxHeartRate,
        .VO2max = dataSet1.Vo2Max,
        .size = sizeof(maxHeartRate_data.x),
        .name = "max heart rate vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //Cumulative hits TODO: definition
    dataSet cumulativeHits_data = {
        .x = dataSet1.cumulativeHits,
        .VO2max = dataSet1.Vo2Max,
        .size = sizeof(cumulativeHits_data.x),
        .name = "cumulative hits vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //Cumulative Runs TODO: definition
    dataSet cumulativeRuns_data = {
        .x = dataSet1.cumulativeRuns,
        .VO2max = dataSet1.Vo2Max,
        .size = sizeof(cumulativeRuns_data.x),
        .name = "cumulative runs vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //training hours
    dataSet trainingHours_data = {
        .x = dataSet1.trainingHoursPerWeek,
        .VO2max = dataSet1.Vo2Max,
        .size = sizeof(trainingHours_data.x),
        .name = "training hours vs. V02max",
        .weight = 0,
        .bias = 0
    };

    //array med alle datasets
    dataSet dataSets [] = {age_data, weight_data, restingHeartRate_data, maxHeartRate_data, cumulativeHits_data, cumulativeRuns_data, trainingHours_data};
    int num_dataSets = 7;

    //splitter dataset (WIP)
    for(int k; k < num_dataSets - 1; k++){
        split_datasets(&dataSets[k], dataSets, 0.8);
    }
    split_datasettester(&trainingHours_data, 0.8);
    
    /*
    //Regression
    int epoch = 100000;
    double learningRate = 0.0001;
    int size = sizeof(age_data.x) / sizeof(age_data.x[0]);
    double loss = 0;
    double gradW = 0;
    double gradB = 0;
    
    for (int i = 1; i <= epoch; i++ ){
        loss = cost(&age_data);
        gradW = weightGrad(&age_data);
        gradB = biasGrad(&age_data);
        
        age_data.weight = age_data.weight - learningRate * gradW;
        age_data.bias = age_data.bias - learningRate * gradB;
        
        printf("Epoch %d ---- Loss: %lf \n", i, loss);
        printf("Weight: %lf, Bias: %lf, GradW: %lf, GradB: %lf\n\n", age_data.weight, age_data.bias, gradW, gradB);
    }
    
    printf("Model Loss: %lf\n", loss);
    printf("Optimum Weight: %lf\n", age_data.weight);
    printf("Optimum Bias: %lf\n\n", age_data.bias);   
    */

    
    for(int i = 0; i < num_dataSets - 1; i++){
        testRegression(&dataSets[i]);
        printf("Loop Number: %d\n", i);
    }
    
    /*
    ////TESTER
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
    }///TESTER

    ////TESTER
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

    free(predictions); //frigøre data igen (malloc)
    */
    return 0;
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

static double cost(dataSet* data){
    double lossValue = 0;
    double sumLoss = 0;
    double* yPredicted = predict(data);

    for (int i = 0; i < data->size; i++){
        lossValue = (data->x[i] - yPredicted[i]) * (data->x[i] - yPredicted[i]);
        sumLoss += lossValue;
    }

    free(yPredicted);
    return sumLoss / (2 * data->size);
}

static double weightGrad(dataSet* data){
    double grad = 0;
    double* yPredicted = predict(data);

    for(int i; i < data->size; i++){
        grad += (yPredicted[i] - data->x[i]) * data->VO2max[i];
    }

    free(yPredicted);
    return grad / data->size;
}

static double biasGrad(dataSet* data){
    double grad = 0;
    double* yPredicted = predict(data);

    for(int i; i < data->size; i++){
        grad += (yPredicted[i] - data->x[i]);
    }

    free(yPredicted);
    return grad / data->size;
}

void testRegression(dataSet* data){
    double* predictions = predict(data);

    for (int i; i < data->size; i++){
        printf("Inputs: %lf,\nPredictions: %lf\n\n", data->x[i], data->VO2max[i]);
    }

    free(predictions);
}

void testLoad(dataLoad test) {
    for (int i = 0; i < 1000; i++) {
        printf("%d %d %d %d %d %lf %d %d %d \n",
            test.age[i],
            test.heightCm[i],
            test.weightKg[i],
            test.restingHeartRate[i],
            test.maxHeartRate[i],
            test.Vo2Max[i],
            test.cumulativeHits[i],
            test.cumulativeRuns[i],
            test.trainingHoursPerWeek[i]);

        }
}
