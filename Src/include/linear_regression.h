#ifndef FITNESSTRACKER_LINEAR_REGRESSION_H
#define FITNESSTRACKER_LINEAR_REGRESSION_H

typedef struct {
    double x;
    double y;
} dataLoad;

typedef struct {
    double slope;
    double intercept;
    double r_squared;
} regressionResult;

int regression();

#endif //FITNESSTRACKER_LINEAR_REGRESSION_H