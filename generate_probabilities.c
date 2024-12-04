#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void normalize(float* array, int size) {
    float sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    for (int i = 0; i < size; i++) {
        array[i] /= sum;
    }
}
int main() {
    int n = 1000000;
    float probabilities[1000000];
    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        probabilities[i] = (float)rand() / RAND_MAX; 
    }
        normalize(probabilities, n);
        for (int i = 0; i < n; i++) {
        printf("%f", probabilities[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n"); 
    return 0;
}