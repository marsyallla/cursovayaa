#ifndef SIMULATION_H
#define SIMULATION_H

void normalize(float* probability, int size);
void allsum(float* probability, float* allsums, int size);
void simulate(int n, float* probability, int y, int* result, int method);

#endif