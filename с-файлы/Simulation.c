#include "simulation.h"
#include <stdlib.h>
#include <time.h>

void normalize(float* probability, int size) {
    float sum = 0.0;
    int i; 
    for (i = 0; i < size; i++) {
        sum += probability[i];
    }
    for (i = 0; i < size; i++) {
        probability[i] /= sum;
    }
}

void allsum(float* probability, float* allsums, int size) {
    int i;
    allsums[0] = probability[0];
    for (i = 1; i < size; i++) {
        allsums[i] = allsums[i - 1] + probability[i];
    }
}
