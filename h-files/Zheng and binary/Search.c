#include "search.h"
#include <stdlib.h>
#include <math.h>

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

double getalpha() {
    return (double)rand() / RAND_MAX;
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
    int j = (int)ceil(m * random);  
    if (j >m) {
        j = m;
    }

    int i = r[j - 1];
    while (i > 0 && random > s[i - 1]) {
        i++;
        if (i >= m)
            break;
    }
    return i - 1;
}