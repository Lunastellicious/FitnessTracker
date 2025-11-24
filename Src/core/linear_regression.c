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
// Skal omskrives med egne ord (Dette er næsten en til en med kilden)
// cost function
static double cost(double inputs[], double observedOutputs[], int size, double weight, double bias){
    double loss = 0;
    double sumLoss = 0;
    double* predictedOutputs = predict(inputs, size, weight, bias);

    for (int i = 0; i < size; i++){
        loss = (observedOutputs[i] - predictedOutputs[i]) * (observedOutputs[i] - predictedOutputs[i]);
        sumLoss += loss;
    }
    free(predictedOutputs);
    return sumLoss / (2 * size);
}

// Gradients of Weights
static double weightGrad(double inputs[], double observedOutputs[], int size, double weight, double bias) {
    double grad = 0;
    double* predictedOutputs = predict(inputs, size, weight, bias);

    for (int i = 0; i < size; i++) {
        grad += (predictedOutputs[i] - observedOutputs[i]) * inputs[i];
    }

    free(predictedOutputs);
    return grad / size;
}

// Gradients of Bias
static double biasGrad(double inputs[], double observedOutputs[], int size, double weight, double bias) {
    double grad = 0;
    double* predictedOutputs = predict(inputs, size, weight, bias);

    for (int i = 0; i < size; i++) {
        grad += (predictedOutputs[i] - observedOutputs[i]);
    }

    free(predictedOutputs);
    return grad / size;
}