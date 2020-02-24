#ifndef VECTOR_EXT_H
#define VECTOR_EXT_H

#if defined(__x86_64)
#include <x86intrin.h>
#elif defined(__aarch64__)
#include "arm_neon.h"
#else
#error "Unknown architecture"
#endif

#if defined(__aarch64__)

// TODO
typedef __m256d float64x4_t 
#define _mm256_load_pd(PTR)
#define _mm256_broadcast_sd(PTR)
#define _mm256_add_pd(A, B)
#define _mm256_mul_pd(A, B)
#define _mm256_store_pd(PTR, A)

#endif

#endif
