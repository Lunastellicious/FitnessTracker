//
// Created by lunas on 04-11-2025.
//

#include "data.h"
// Definition of the Database structure
// Fake-abase
struct Database {
    union{
        struct { } current;
        struct { } previous;
    };
    int id;
};