#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "simulation.h"
#include "search.h"

double get_time_diff(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

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
    int* result_zhen = (int*)calloc(n, sizeof(int));
    if (result_binary == NULL || result_zhen == NULL) {
        printf("Memory allocation failed\n");
        free(probability);
        return 1;
    }

    srand(time(NULL));

    float* random_binary = (float*)malloc(y * sizeof(float));
    float* random_zhen = (float*)malloc(y * sizeof(float));

    for (int i = 0; i < y; i++) {
        random_binary[i] = (float)rand() / RAND_MAX;
        random_zhen[i] = (float)rand() / RAND_MAX;
    }

    float* allsums = (float*)malloc(n * sizeof(float));
    allsum(probability, allsums, n);  

    float* s = (float*)malloc(n * sizeof(float));  
    int* r = (int*)malloc(y * sizeof(int));       

    zhen_precompute(n, y, probability, s, r);  

    struct timeval start_time_binary, end_time_binary;
    gettimeofday(&start_time_binary, NULL);
    simulate(n, probability, y, result_binary, 0, random_binary, allsums, s, r);
    gettimeofday(&end_time_binary, NULL);

    struct timeval start_time_zhen, end_time_zhen;
    gettimeofday(&start_time_zhen, NULL);
    simulate(n, probability, y, result_zhen, 1, random_zhen, allsums, s, r);
    gettimeofday(&end_time_zhen, NULL);

    printf("Results:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: Binary=%d, Zhen=%d\n", i, result_binary[i], result_zhen[i]);
    }

    printf("\nChecking probabilities:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: Probability=%f, Binary_approx=%f, Zhen_approx=%f\n",
               i, probability[i], (float)result_binary[i] / y, (float)result_zhen[i] / y);
    }

    printf("Binary Search: %.10f seconds\n", get_time_diff(start_time_binary, end_time_binary));
    printf("Zhen Search: %.10f seconds\n", get_time_diff(start_time_zhen, end_time_zhen));

    free(probability);
    free(result_binary);
    free(result_zhen);
    free(random_binary);
    free(random_zhen);
    free(allsums);
    free(s);
    free(r);

    return 0;
}