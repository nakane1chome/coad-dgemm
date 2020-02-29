#ifndef DGEMM_HPP
#define DGEMM_HPP

void dgemm_unopt(int n, double *A, double * B, double *C);
void dgemm_cache_blocking(int n, double *A, double * B, double *C);

#endif
