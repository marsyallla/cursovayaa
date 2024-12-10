#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 1000;
    FILE* file = fopen("1000code.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    float* probabilities = (float*)malloc(n * sizeof(float));
    if (probabilities == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));
    float sum = 0.0;
    for (int i = 0; i < n; i++) {
        probabilities[i] = (float)rand() / RAND_MAX;  
        sum += probabilities[i];
    }

    for (int i = 0; i < n; i++) {
        probabilities[i] /= sum;
    }

    // Запись в файл
    fprintf(file, "%d\n", n); 
    for (int i = 0; i < n; i++) {
        fprintf(file, "%f ", probabilities[i]);
    }
    fprintf(file, "\n");
    fprintf(file, "100000\n"); 

    fclose(file);
    free(probabilities);
    return 0;