#include <stdio.h>
#include "simulation.h"
#include <stdlib.h>
#include <time.h>
#include "search.h"

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

void inverse_method_function(int n, int m, float* p, int* r, float* s) {
    srand(time(NULL));
    s[0] = p[0];
    for (int k = 1; k < n; k++) {
        s[k] = s[k - 1] + p[k];
    }
    for (int j = 0; j < m; j++) {
        float xi = (float)rand() / RAND_MAX;
        int i=0;
        while (i < n && s[i] < xi) {
            i++;
        }
        r[i]++;
    }
}