#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
int main(int argc, char** argv) {
    int n, y;

    if (argc < 2) {
        printf("Used: %s <input_file>\n", argv[0]);
        return 1;
    }
    FILE* file;
    errno_t err = fopen_s(&file, "input.txt", "r");
    if (err != 0 || file == NULL) {
    printf("Error opening file\n");
    return 1;
}
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fscanf_s(file, "%d", &n);
    float* probability = (float*)malloc(n * sizeof(float));
    float* allsums = (float*)malloc(n * sizeof(float));
    if (probability == NULL || allsums == NULL) {
        printf("Memory failed\n");
        fclose(file);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        fscanf_s(file, "%f", &probability[i]);
    }

    fscanf_s(file, "%d", &y);
    fclose(file);

    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += probability[i];
    }
    if (sum != 1.0) {
        normalize(probability, n);
    }

    allsum(probability, allsums, n);

    clock_t start_time = clock();
    int* result = (int*)malloc(n * sizeof(int));
    if (result == NULL) {
        printf("Memory failed\n");
        free(probability);
        free(allsums);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        result[i] = 0;
    }
    for (int i = 0; i < y; i++) {
        float xi = (float)rand() / RAND_MAX;
        int ind = binary(allsums, n, xi);
        result[ind]++;
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    for (int i = 0; i < n; i++) {
        printf("Element %d: %d selections\n", i, result[i]);
    }

    printf("Elapsed time: %f seconds\n", elapsed_time);
    free(probability);
    free(allsums);
    free(result);

    return 0;
}