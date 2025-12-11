#ifndef RECOMMENDS_H
#include "linear_regression.h"
#define RECOMMENDS_H

struct metrics {
    int runSPeed;
    int runLength;
    int vo2MaxPos;
} metrics;

void recommend(double distance, double vo2Max, double heartRate, double time, regressionResult a);

#endif // RECOMMENDS_H