#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_probabilities(const char* filename, int count) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "w");
    if (err != 0 || file == NULL) {
        printf("Error opening file\n");
        return;
    }
    float* probabilities = (float*)malloc(count * sizeof(float));
    if (probabilities == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }
    srand((unsigned int)time(NULL));
    for (int i = 0; i < count; i++) {
        probabilities[i] = (float)rand() / RAND_MAX;
    }
    
    for (int i = 0; i < count; i++){
        fprintf(file, "%.6f\n", probabilities[i]);
    }

    printf("Generated %d probabilities and saved to %s\n", count, filename);
    
    free(probabilities);
    fclose(file);
}

int main() {
    const char* filename = "probabilities.txt";
    int count = 1000;
    generate_probabilities(filename, count);
    return 0;
}