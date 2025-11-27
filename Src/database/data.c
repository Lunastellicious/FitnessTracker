#include "../include/data.h"
// Creation of struct update functions
void set_HRrest(Database *a, int HRrest){
    a->HRrest = HRrest;
}
void set_HRmax(Database *a, int HRmax){
    a->HRmax = HRmax;
}
void set_HRaverage(Database *a, int HRaverage){
    a->HRaverage = HRaverage;
}
void set_pace(Database *a, int pace){
    a->pace = pace;
}
void set_duration(Database *a, double duration){
    a->duration = duration;
}
void set_distance(Database *a, double distance){
    a->distance = distance;
}
void set_tempo(Database *a, int tempo){
    a->tempo = tempo;
}