#include <stdio.h>


#ifndef TYPEDEFS_H
#define TYPEDEFS_H


typedef struct{
    int* sin_port;
    int* address;
}Request;

typedef struct{
    int* numeric;
    char* text;
    float* float_num;
    double* double_num;
}List;


#endif