#include "data.h"
// Creation of struct update functions
// Fake-abase
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
void set_duration(Database *a, int duration){
    a->duration = duration;
}
void set_length(Database *a, int length){
    a->length = length;
}
void set_tempo(Database *a, int tempo){
    a->tempo = tempo;
}