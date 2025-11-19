#ifndef DATA_H
#define DATA_H

typedef struct {
    int HRrest,
        HRmax,
        HRaverage,
        pace,
        tempo;
    double duration,
           distance;
} Database;

void set_HRrest(Database *a, int HRrest);
void set_HRmax(Database *a, int HRmax);
void set_HRaverage(Database *a, int HRaverage);
void set_pace(Database *a, int pace);
void set_duration(Database *a, double duration);
void set_distance(Database *a, double distance);
void set_tempo(Database *a, int tempo);
#endif //DATA_H