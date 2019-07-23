#ifndef WHEEL_FACTORISER
#define WHEEL_FACTORISER
#include "vector.h"
typedef struct wheel wheel;
struct wheel {
  vector* base;
  vector* primes;
  int max_number;
  int min_number;
  int next_base;
};

wheel* wheel_init();
void wheel_free();
vector* primes_below_n(wheel* factor, int n);

#endif
