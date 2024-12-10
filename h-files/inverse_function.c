#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulation.h"

int main(int argc, char** argv) {
    int n, y;
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf(file, "%d", &n);
    float* probability = (float*)malloc(n * sizeof(float));
    if (probability == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%f", &probability[i]);
    }

    fscanf(file, "%d", &y);
    fclose(file);

    normalize(probability, n);

    int* result_binary = (int*)calloc(n, sizeof(int));
    int* result_inverse = (int*)calloc(n, sizeof(int));
    if (result_binary == NULL || result_inverse == NULL) {
        printf("Memory allocation failed\n");
        free(probability);
        return 1;
    }

    clock_t start_time_binary = clock();
    simulate(n, probability, y, result_binary, 0);
    clock_t end_time_binary = clock();

    clock_t start_time_inverse = clock();
    simulate(n, probability, y, result_inverse, 1);
    clock_t end_time_inverse = clock();

    printf("Results:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: Binary=%d, Inverse=%d\n", i, result_binary[i], result_inverse[i]);
    }

    printf("\nChecking probabilities:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: Probability=%f, Binary_approx=%f, Inverse_approx=%f\n",
               i, probability[i], (float)result_binary[i] / y, (float)result_inverse[i] / y);
    }

    printf("Binary Search: %.10f seconds\n", (double)(end_time_binary - start_time_binary) / CLOCKS_PER_SEC);
    printf("Inverse Method Function: %.10f seconds\n", (double)(end_time_inverse - start_time_inverse) / CLOCKS_PER_SEC);

    free(probability);
    free(result_binary);
    free(result_inverse);

    return 0;
}