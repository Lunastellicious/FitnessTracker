#ifndef RECOMMENDS_H
#include "linear_regression.h"
#include "data.h"
#define RECOMMENDS_H

typedef struct {
    int runSPeed;
    int runLength;
    int vo2MaxPos;
} metrics;

void recommend(Database* current, regressionResult* a);

#endif // RECOMMENDS_H