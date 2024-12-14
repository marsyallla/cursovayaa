#include "simulation.h"
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

void initialize_r(int n, int m, float* s, int* r) {
    int i = 0;
    for (int j = 1; j <= m; j++) {
        while (i < n && s[i] < (float)(j - 1) / m) {
            i++;
        }
        r[j - 1] = i;
    }
}

int zhen_sample(int n, int m, float* s, int* r) {
    float alpha = (float)rand() / RAND_MAX; 
    int j = (int)(m * alpha);              
    if (j >= m) j = m - 1;

    int i = r[j]; 
    while (i < n && alpha > s[i]) {
        i++;
    }
    return i;
}

void simulate_zhen(int n, float* probability, int y, int* result, float* random) {
    float* allsums = (float*)malloc(n * sizeof(float));
    int* r = (int*)malloc(y * sizeof(int));

    allsum(probability, allsums, n);
    initialize_r(n, y, allsums, r);

    for (int i = 0; i < y; i++) {
        int index = zhen_sample(n, y, allsums, r);
        result[index]++;
    }

    free(allsums);
    free(r);
}

int binary(float* allsums, int size, float xi) {
    int left = 0, right = size - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (allsums[mid] < xi)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void simulate_binary(int n, float* probability, int y, int* result, float* random) {
    float* allsums = (float*)malloc(n * sizeof(float));
    allsum(probability, allsums, n);

    for (int i = 0; i < y; i++) {
        float xi = random[i];
        int ind = binary(allsums, n, xi);
        result[ind]++;
    }

    free(allsums);
}