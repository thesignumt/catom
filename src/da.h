#ifndef CATOM_DA_H_
#define CATOM_DA_H_

#include <stddef.h>
#include <stdlib.h>

typedef struct {
  size_t count;
  size_t capacity;
} da__Header;

#define ARR_INIT_CAPACITY 1

#define da__hdr(a) ((da__Header *)(a) - 1)

#define da_len(a) ((a) ? da__hdr(a)->count : 0)

#define da_cap(a) ((a) ? da__hdr(a)->capacity : 0)

#define da_free(a)      \
  do {                  \
    if (a) {            \
      free(da__hdr(a)); \
      (a) = NULL;       \
    }                   \
  } while (0)

#define da__grow(a, n)                                              \
  do {                                                              \
    size_t new_cap = da_cap(a) ? da_cap(a) * 2 : ARR_INIT_CAPACITY; \
    if (new_cap < (n)) new_cap = (n);                               \
                                                                    \
    size_t size = sizeof(da__Header) + sizeof(*(a)) * new_cap;      \
    da__Header *new_hdr;                                            \
                                                                    \
    if (a)                                                          \
      new_hdr = realloc(da__hdr(a), size);                          \
    else {                                                          \
      new_hdr = malloc(size);                                       \
      if (new_hdr) new_hdr->count = 0;                              \
    }                                                               \
                                                                    \
    new_hdr->capacity = new_cap;                                    \
    (a) = (void *)(new_hdr + 1);                                    \
  } while (0)

#define da_push(a, v)               \
  do {                              \
    if (da_len(a) >= da_cap(a)) {   \
      da__grow(a, da_len(a) + 1);   \
    }                               \
    (a)[da__hdr(a)->count++] = (v); \
  } while (0)

#endif  // CATOM_DA_H_
