#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulation.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int n, y;
    fscanf(file, "%d", &n);
    float* probability = (float*)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++) {
        fscanf(file, "%f", &probability[i]);
    }
    fscanf(file, "%d", &y);
    fclose(file);

    normalize(probability, n);

    int* result_binary = (int*)calloc(n, sizeof(int));
    int* result_zhen = (int*)calloc(n, sizeof(int));
    float* random = (float*)malloc(y * sizeof(float));

    srand(time(NULL));
    for (int i = 0; i < y; i++) {
        random[i] = (float)rand() / RAND_MAX;
    }

    clock_t start_binary = clock();
    simulate_binary(n, probability, y, result_binary, random);
    clock_t end_binary = clock();

    clock_t start_zhen = clock();
    simulate_zhen(n, probability, y, result_zhen, random);
    clock_t end_zhen = clock();

    printf("Results:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: Binary=%d, Zhen=%d\n", i, result_binary[i], result_zhen[i]);
    }

    printf("\nTiming:\n");
    printf("Binary Search: %.10f seconds\n", (double)(end_binary - start_binary) / CLOCKS_PER_SEC);
    printf("Zhen Method: %.10f seconds\n", (double)(end_zhen - start_zhen) / CLOCKS_PER_SEC);

    free(probability);
    free(result_binary);
    free(result_zhen);
    free(random);

    return 0;
}