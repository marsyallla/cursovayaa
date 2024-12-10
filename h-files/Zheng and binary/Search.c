#include <stdio.h>
#include "simulation.h"
#include <stdlib.h>
#include <time.h>
#include "search.h"
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

double zhen(int n, int m, double p[], double s[], int r[]) {
     int i = 1;
    s[0] = p[0];

    for (int k = 1; k < n; k++)
        s[k] = s[k - 1] + p[k];

    for (int j = 1; j <= m; j++) {
        while (i < n && s[i] <= (double)(j - 1) / m)
            i++;
        r[j - 1] = i;
    }

    double alpha = getalpha();
    int j = (int)ceil(m * alpha);
    if (j > m)
        j = m;

    i = r[j - 1];

    while (alpha > s[i - 1]) {
        i++;
        if (i >= n)
            break;
    }

    return s[i - 1];
}