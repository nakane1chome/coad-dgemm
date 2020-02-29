
//
// Derived from Computer Organization and design : The hardware/software interface
// Figure 5.47 Optimized C version of DGEMM Example, using cache blocking

#include "dgemm.hpp"
#include "vector_ext.h"

#define UNROLL (4)
#define BLOCKSIZE (32)

void do_block(int n, int si, int sj, int sk, 
              double *A, double *B, double *C) {
    for (int i=si; i < si+BLOCKSIZE; i+= UNROLL*VECTOR_LENGTH) {
        for (int j=sj; j < sj+BLOCKSIZE; j++) {
            double_vec_t c[UNROLL];
            for (int x=0; x<UNROLL; x++) {
                c[x] = _vector_load_pd(C+i+x*VECTOR_LENGTH+j*n);
            } // x
            // c[x] = C[i][j];
            for (int k=sk; k < sk + BLOCKSIZE; k++) {
                double_vec_t b = _vector_broadcast_sd(B+j*n+k);
                for (int x=0; x<UNROLL; x++) {
                    double_vec_t a = _vector_load_pd(A+k*n+i+x*VECTOR_LENGTH);
                    // c[x] += A[i][k]*b
                    c[x] = _vector_add_pd(c[x], _vector_mul_pd(a, b));
                } // x
                
            } // k 
            for (int x=0; x<UNROLL; x++) {
                _vector_store_pd(C+i+x*VECTOR_LENGTH+j*n, c[x]);
            } // x
        } // j
    } // i
} // do_block            

void dgemm_cache_blocking(int n, double *A, double * B, double *C) {
    for (int si=0; si < n; si += BLOCKSIZE) {
        for (int sj=0; sj < n; sj += BLOCKSIZE) {
            for (int sk=0; sk < n; sk += BLOCKSIZE) {
                do_block(n, si, sj, sk, A, B , C);
            }
        }
    }
}
