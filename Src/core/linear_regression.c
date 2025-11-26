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
static double cost(double xValues[], double observedOutputs[], int size, double weight, double bias){
    double sumLoss = 0.0;
    double* predictedOutputs = predict(xValues, size, weight, bias);

    for (int i = 0; i < size; i++){
        double loss = (observedOutputs[i] - predictedOutputs[i]);
        sumLoss += loss * loss;
    }
    free(predictedOutputs);
    return sumLoss / (size * 2);
}

// Gradients of Weights
// This implementation of the gradients of weight/slope function is heavily inspired by a source on linear regression.
static double weightGrad(double inputs[], double observedOutputs[], int size, double weight, double bias) {
    double grad = 0;
    double* predictedOutputs = predict(inputs, size, weight, bias);

    for (int i = 0; i < size; i++){
        grad += (predictedOutputs[i] - observedOutputs[i]) * inputs[i];
    }
    free(predictedOutputs);
    return grad / size;
}

// Gradients of Bias
// This implementation of the gradients of bias/intercept function is heavily inspired by a source on linear regression.
static double biasGrad(double inputs[], double observedOutputs[], int size, double weight, double bias) {
    double grad = 0;
    double* predictedOutputs = predict(inputs, size, weight, bias);

    for (int i = 0; i < size; i++){
        grad += (predictedOutputs[i] - observedOutputs[i]);
    }
    free(predictedOutputs);
    return grad / size;
}

