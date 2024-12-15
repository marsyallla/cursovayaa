#ifndef SEARCH_H
#define SEARCH_H
int binary(float* allsums, int size, float xi);
double getalpha();
void zhen_precompute(int n, int m, float* p, float* s,int *r);
int zhen_simulate(int m, float*s, int *r, float random);

#endif  // SEARCH_H