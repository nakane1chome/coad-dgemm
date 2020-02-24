#include <stdlib.h>

extern void dgemm_unopt(int n, double *A, double * B, double *C);
extern void dgemm_cache_blocking(int n, double *A, double * B, double *C);

#define ALIGNMENT 256
#include "mem_util.h"

void randomize_matrix(double *M, int n);

int main(int argc, char **argv) {
    
    const int n = 128;
    const size_t buffer_size = n*n*sizeof(double);
    double *A = aligned_alloc(ALIGNMENT, buffer_size);
    double *B = aligned_alloc(ALIGNMENT, buffer_size);
    double *C0 = aligned_alloc(ALIGNMENT, buffer_size);
    double *C1 = aligned_alloc(ALIGNMENT, buffer_size);
    randomize_matrix(A, n);
    randomize_matrix(B, n);
    randomize_matrix(C0, n);
    randomize_matrix(C1, n);

    dgemm_unopt(n, A, B, C0);
    dgemm_cache_blocking(n, A, B, C1);


}

void randomize_matrix(double *M, int n) {
    for (int i=0; i<n;i++) {
        for (int j=0; j<n;j++) {
            M[i*n + j] = ((double) rand())/ RAND_MAX;
        }
    }
}
