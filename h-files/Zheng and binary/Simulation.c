#include "simulation.h"
#include "search.h"
#include <stdlib.h>

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
void zhen_precompute(int n, int m, float* p, float* s, int* r) {
    s[0] = p[0];
    for (int k = 1; k < n; k++) {
        s[k] = s[k - 1] + p[k];
    }

    int i = 1;
    for (int j = 1; j <= m; j++) {
        while (i < n && s[i - 1] <= (float)(j - 1) / m) {
            i++;
        }
        r[j - 1] = i;
    }
}

int zhen_simulate(int m, float* s, int* r, float random) {
    int j = (int)(m * random) + 1; 
    if (j > m) {
        j = m;
    }

    int i = r[j - 1];
    while (i > 0 && random > s[i - 1]) {
        i++;
    }
    return i - 1;  
}
void simulate(int n, float* probability, int y, int* result, int method, float* random) {
    float* allsums = (float*)malloc(n * sizeof(float));
    int* r = NULL;  
    float* s = NULL;
    if (method == 1) {
        r = (int*)malloc(y * sizeof(int));
        s = (float*)malloc(n * sizeof(float));
        zhen_precompute(n, y, probability, s, r);
    } else {
        allsum(probability, allsums, n);
    }

    for (int i = 0; i < y; i++) {
        float xi = random[i];
        int index = 0;

        if (method == 0) {
            index = binary(allsums, n, xi);
        } else {
            index = zhen_simulate(y, s, r, xi);
        }
        result[index]++;
    }

    free(allsums);
    if (method == 1) {
        free(r);
        free(s);
    }
}