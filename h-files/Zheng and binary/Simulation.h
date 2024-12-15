#ifndef SIMULATION_H
#define SIMULATION_H

void normalize(float* probability, int size);
void allsum(float* probability, float* allsums, int size);
void initialize_r(int n, int m, float* s, int* r);
int zhen_sample(int n, int m, float* s, int* r);
void simulate_binary(int n, float* probability, int y, int* result, float* random);
void simulate_zhen(int n, float* probability, int y, int* result, float* random);

#endif