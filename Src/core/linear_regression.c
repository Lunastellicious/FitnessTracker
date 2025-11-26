//
// Created by lunas on 24-11-2025.
//

#include "../include/linear_regression.h"
#include <stdlib.h>
#include <stdio.h>

static double cost(double inputs[], double observedOutputs[], int size, double weight, double bias);
static double weightGrad(double inputs[], double observedOutputs[], int size, double weight, double bias);
static double biasGrad(double inputs[], double observedOutputs[], int size, double weight, double bias);

int main ()
{

}

// cost function
// This implementation of the cost function is heavily inspired by a source on linear regression.
static double cost(dataSet* data){
    double sumLoss = 0.0;
    double* predictedOutputs = predict(dataSet* data);

    for (int i = 0; i < data->train_size; i++){
        double loss = (data->VO2max_train[i] - predictedOutputs[i]);
        sumLoss += loss * loss;
    }
    free(predictedOutputs);
    return sumLoss / ((data->train_size) * 2);
}

// Gradients of Weights
// This implementation of the gradients of weight/slope function is heavily inspired by a source on linear regression.
static double weightGrad(dataSet* data) {
    double grad = 0;
    double* predictedOutputs = predict(dataSet* data);

    for (int i = 0; i < data->train_size; i++){
        grad += (predictedOutputs[i] - data->VO2max_train[i]) * data->x_train[i];
    }
    free(predictedOutputs);
    return grad / data->train_size;
}

// Gradients of Bias
// This implementation of the gradients of bias/intercept function is heavily inspired by a source on linear regression.
static double biasGrad(dataSet* data) {
    double grad = 0;
    double* predictedOutputs = predict(dataSet* data);

    for (int i = 0; i < data->train_size; i++){
        grad += predictedOutputs[i] - data->VO2max_train[i];
    }
    free(predictedOutputs);
    return grad / data->train_size;
}

