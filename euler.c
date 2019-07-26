#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "wheel_factoriser.h"

typedef struct pair pair;
struct pair {
  int car;
  int cdr;
};

pair cons (int car, int cdr) {
  pair cell = {.car = car, .cdr = cdr};
  return cell;
}

int car (pair in) {
  return in.car;
}

pair triangular_dimensions (int triangular_index) {
  double double_index = (double)triangular_index;
  int height = (int)(floor(double_index / 2) * 2) + 1;
  int width = (int)ceil(double_index /2);
  return cons(width, height);
}

int triangular (int index) {
  int triangle = 0;
  for (int i = 1; i <= index; i++) {
    triangle += i;
  }
  return triangle;
}

int divisor_score (int num, int den) {
  int score = 0;
  int remainder = num % den;
  while (remainder == 0) {
    score++;
    num /= den;
    remainder = num % den;
  }
  return score;
}

int factor_count (wheel* factor, int n) {
  vector* primes = primes_below_n(factor, n);
  if(n == 1) {
    return 1;
  }
  int count = 1;
  for (int i = 0; i < primes->length; i++) {
    int score = divisor_score(n, vector_element(primes, i));
    count *= score != 0 ? score + 1 : 1;
  }
  return count;
}

int triangular_factor_count (wheel* factor, int tri_index) {
  pair dims = triangular_dimensions(tri_index);
  int total = factor_count(factor, dims.car) * factor_count(factor, dims.cdr);
  return total;
}

int main(int argc, char* argv[]) {
  wheel* factor = wheel_init();
  int divisors = 0;
  int i = 3;

  while (i <= 20000) {
    // divisors = triangular_factor_count(factor, i);
    divisors = factor_count(factor, triangular(i));
    if (divisors > 500) {
      break;
    }
    if (i == 20000) {
      printf("iterator exceeded 20,000");
      break;
    }
    i++;
  }
  printf("I: %d, N: %d, F: %d\n", i, triangular(i), triangular_factor_count(factor, i));

  return 0;
}
