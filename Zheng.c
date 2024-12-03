#include <stdio.h>
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
void zhen(int n, int m, float* p, int* r, float* s) {
    int i = 1;
    s[0] = p[0];
    for (int k = 1; k < n; k++) {
        s[k] = s[k - 1] + p[k];
    }
    for (int j = 1; j <= m; j++) {
        while (i < n && s[i - 1] <= (float)(j - 1) / m) {
            i++;
        }
        r[j - 1] = i;
    }
}
void simulation(int m, int n, float* x, float* s, int* r, int* result) {
    double random = (double)rand() / RAND_MAX;
    int j = (int)(m * random);
    if (j >= m) j = m - 1; // 
    int i = r[j];
    while (i < n && random > s[i]) {
        i++;
    }
    if (i < n) {
        result[i]++;
    }
}
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file;
    errno_t err = fopen_s(&file, argv[1], "r");
    if (err != 0 || file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int n, m;
    fscanf_s(file, "%d", &n); 
    fscanf_s(file, "%d", &m);
    float* probability = (float*)malloc(n * sizeof(float));
    float* allsums = (float*)malloc(n * sizeof(float));
    if (probability == NULL || allsums == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf_s(file, "%f", &probability[i]); 
    }
    fclose(file);

    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += probability[i];
    }
   if (sum != 1.0) { 
        normalize(probability, n);
    }
    int* r = (int*)malloc(m * sizeof(int));
    int* counts = (int*)calloc(n, sizeof(int));
    if (r == NULL || counts == NULL) {
        printf("Memory allocation failed\n");
        free(probability);
        free(allsums);
        return 1;
    }
    clock_t start = clock();
    zhen(n, m, probability, r, allsums);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time for Zhen : %f seconds\n", elapsed_time);
    start = clock();
    for (int i = 0; i < 100000; i++) {
        simulation(m, n, probability, allsums, r, counts);
    }
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Elapsed time for simulation: %f seconds\n", elapsed_time);
    for (int i = 0; i < n; i++) {
        printf("Element %d: %d selections\n", i + 1, counts[i]);
    }
    free(probability);
    free(allsums);
    free(counts);
    free(r);

    return 0;
}