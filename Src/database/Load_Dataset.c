//
// Created by nadod on 24-11-2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int age[1000];
    int heightCm[1000];
    int weightKg[1000];
    int restingHeartRate[1000];
    int maxHeartRate[1000];
    double Vo2Max[1000];
    int cumulativeHits[1000];
    int cumulativeRuns[1000];
    int trainingHoursPerWeek[1000];
} dataSet;

void test(dataSet test);
void loadDataSet();

int main(void) {
    loadDataSet();
}


void loadDataSet() {
    dataSet dataSet1;
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
    test(dataSet1);
    fclose(fData);

}

void test(dataSet test) {
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



