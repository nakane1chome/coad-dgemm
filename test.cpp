#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <iostream>


#define ALIGNMENT 256
#include "mem_util.h"
#include "profile_util.hpp"

#include "dgemm.hpp"

void randomize_matrix(double *M, int n);
void zero_matrix(double *M, int n);
bool compare_matrix(int n, double *A,double *B);

int main(int argc, char **argv) {
    
    const int n = 128;
    const size_t buffer_size = n*n*sizeof(double);
    profiler p("dgemm");
    double *A  = (double *) aligned_alloc(ALIGNMENT, buffer_size);
    double *B  = (double *) aligned_alloc(ALIGNMENT, buffer_size);
    double *C0 = (double *) aligned_alloc(ALIGNMENT, buffer_size);
    double *C1 = (double *) aligned_alloc(ALIGNMENT, buffer_size);
    randomize_matrix(A, n);
    randomize_matrix(B, n);
    zero_matrix(C0, n);
    zero_matrix(C1, n);

    p.start("unopt");
    dgemm_unopt(n, A, B, C0);
    p.end();
    
    p.start("cache_blocking");
    dgemm_cache_blocking(n, A, B, C1);
    p.end();

    if (compare_matrix(n, C0, C1)) {
        printf("ERROR: unoptimized and cache blocking mismatch\n");
        return 1;
    }

    printf("Results Match: Passed.\n");

    p.report(std::cout);

    return 0;
}

void randomize_matrix(double *M, int n) {
    for (int i=0; i<n;i++) {
        for (int j=0; j<n;j++) {
            M[i*n + j] = ((double) rand())/ RAND_MAX;
        }
    }
}
void zero_matrix(double *M, int n) {
    for (int i=0; i<n;i++) {
        for (int j=0; j<n;j++) {
            M[i*n + j] = 0.0;
        }
    }
}
bool compare_matrix(int n, double *A,double *B)  {
    for (int i=0; i<n;i++) {
        for (int j=0; j<n;j++) {
            double diff = A[i*n + j] - B[i*n + j];
            if ((diff < -0.02) || (diff > 0.02)) {
                printf("ERROR: %d, %d: %f != %f, diff=%f\n", i, j, A[i*n + j], B[i*n + j], diff);
                return true;
            }
        }
    }
    return false;
}
