#ifndef MEM_UTIL_H
#define MEM_UTIL_H

#include <malloc.h>
#include <stdint.h>

#ifdef _WIN32
#define aligned_alloc(ALIGNMENT, SIZE) \
    _aligned_malloc(SIZE, ALIGNMENT)
#endif

static inline size_t align_size(size_t size) {
    return (size & (~(ALIGNMENT-1))) + ALIGNMENT;
}

#endif
