#ifndef SIMULATION_H
#define SIMULATION_H

void normalize(float* probability, int size);
void allsum(float* probability, float* allsums, int size);
void zhen_precompute(int n, int m, float* p,float* s, int* r);
int zhen_simulate(int m, float* s,int* r, float random);
void simulate(int n, float* probability, int y, int* result, int method, float* random);
#endif