#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "wheel_factoriser.h"

int main(int argc, char** argv) {
  wheel* twheel = wheel_init();
  vector* tvec = primes_below_n(twheel, 50);
  print_vector(*tvec);
  return 0;
}
