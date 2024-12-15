#include "simulation.h"
#include "search.h"
#include <stdlib.h>
#include <time.h>

void normalize(float* probability, int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += probability[i];
    }
    for (int i = 0; i < size; i++) {
        probability[i] /= sum;
    }
}

void allsum(float* probability, float* allsums, int size) {
    allsums[0] = probability[0];
    for (int i = 1; i < size; i++) {
        allsums[i] = allsums[i - 1] + probability[i];
    }
}

void simulate(int n, float* probability, int y, int* result, int method, float* random, float* allsums, float* s, int* r) {
    if (method == 0) {  
        for (int i = 0; i < y; i++) {
            float xi = random[i];
            int ind = binary(allsums, n, xi);
            result[ind]++;
        }
    } else {  
        for (int i = 0; i < y; i++) {
            float xi = random[i];
            int index = zhen_simulate(y, s, r, xi);  
            result[index]++;
        }
    }
}