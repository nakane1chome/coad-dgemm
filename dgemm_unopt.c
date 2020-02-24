//
// Derived from Computer Organization and design : The hardware/software interface
// Figure 3.19 Unoptimized C version of double precision matrix multiply, widely known as DGEMM.

void dgemm_unopt(int n, double *A, double * B, double *C) {
    
    for (int i=0; i < n; ++i) {
        for (int j=0; j < n; ++j) {
            double cij = C[i+j*n];
            for (int k=0; k< n; k++) {
                cij += A[i+k*n] * B[k+j*n];
            } // k
            C[i+j*n] = cij;
        } // j
    } // i
}
