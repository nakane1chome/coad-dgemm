#ifndef VECTOR_EXT_H
#define VECTOR_EXT_H

#if defined(__x86_64)
#include <x86intrin.h>
#elif defined(__aarch64__)
#include "arm_neon.h"
#else
#error "Unknown architecture"
#endif

#if defined(__x86_64)

#define VECTOR_LENGTH 4
typedef __m256d double_vec_t ;

#define _vector_load_pd(PTR) _mm256_load_pd(PTR)
#define _vector_broadcast_sd(PTR) _mm256_broadcast_sd(PTR)
#define _vector_add_pd(A, B) _mm256_add_pd(A, B)
#define _vector_mul_pd(A, B) _mm256_mul_pd(A, B)
#define _vector_store_pd(PTR, A) _mm256_store_pd(PTR, A)


#endif

#if defined(__aarch64__)

#define VECTOR_LENGTH 2

// TODO
typedef  float64x2_t double_vec_t;
#define _vector_load_pd(PTR) vld1q_f64(PTR)
#define _vector_broadcast_sd(PTR) vld1q_f64(PTR)
#define _vector_add_pd(A, B) vaddq_f64(A, B)
#define _vector_mul_pd(A, B) vmulq_f64(A, B)
#define _vector_store_pd(PTR, A) vst1q_f64(PTR, A)

#endif

#endif
