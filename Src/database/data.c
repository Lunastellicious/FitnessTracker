#include "data.h"
// Creation of struct update functions
// Fake-abase
void set_HRrest(Database *a, int HRrest){
    a->current.HRrest = HRrest;
}
void set_HRmax(Database *a, int HRmax){
    a->current.HRmax = HRmax;
}
void set_HRaverage(Database *a, int HRaverage){
    a->current.HRaverage = HRaverage;
}
void set_pace(Database *a, int pace){
    a->current.pace = pace;
}
void set_duration(Database *a, int duration){
    a->current.duration = duration;
}
void set_length(Database *a, int length){
    a->current.length = length;
}
void set_tempo(Database *a, int tempo){
    a->current.tempo = tempo;
}