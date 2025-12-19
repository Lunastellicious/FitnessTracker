
#ifndef DATA_H
#define DATA_H
//creation of struct used to store run information
typedef struct {
    int HRrest,
        HRmax,
        HRaverage;
    double duration,
           distance,
           pace,
           VO2max,
           aerobic,
           anaerobic,
           totalTE,
           recovery; 
} Database;

//preloads update functions
void set_HRrest(Database *a, int HRrest);
void set_HRmax(Database *a, int HRmax);
void set_HRaverage(Database *a, int HRaverage);
void set_pace(Database *a, int pace);
void set_duration(Database *a, double duration);
void set_distance(Database *a, double distance);
void set_tempo(Database *a, int tempo);
void set_VO2max(Database *a, int VO2max);
#endif //DATA_H