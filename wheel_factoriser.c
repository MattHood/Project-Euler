#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "wheel_factoriser.h"

int primorial (vector* base) {
  int acc = 1;
  for (int i = 0; i < base->length; i++) {
    acc *= base->contents[i];
  }
  return acc;
}

_Bool divisorp (int num, int den) {
  return num % den == 0;
}

_Bool any_divisor_p (int num, vector* base) {
  _Bool result = 0;
  for (int i = 0; i < base->length && result == 0; i++) {
    result = result || divisorp(num, base->contents[i]);
  }
  return result;
}

int* range_array(int start, int end) {
  assert(start < end);
  int size = end - start;
  int* range = malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) {
    range[i] = i + start;
  }
  return range;
}

void push_if_coprime (int* range, int size, vector* base, vector* dest) {
  for (int i = 0; i < size; i++) {
    if(!any_divisor_p(range[i], base)) {
      vector_push(dest, range[i]);
    }
  }
  return;
}

wheel* wheel_init () {
  wheel* out = malloc(sizeof(wheel));
  out->base = vector_init(1);
  out->primes = vector_init(1);
  int initial_base[] = {2,3};
  vector_push_array(out->base, initial_base, 2);
  vector_push_array(out->primes, initial_base, 2);
  out->min_number = 2;
  out->max_number = primorial(out->base);
  out->next_base = 1;
  return out;
}

void wheel_free (wheel* factor) {
  vector_free(factor->base);
  vector_free(factor->primes);
  free(factor);
  return;
}

void wheel_turn (wheel* factor) {
  // Push primes with current data
  int row_size = factor->max_number - factor->min_number;
  int* row = range_array(factor->min_number, factor->max_number);
  push_if_coprime(row, row_size, factor->base, factor->primes);
  free(row);

  // Update data for the next turn
  factor->next_base++;
  int next_prime = vector_element(factor->primes, factor->next_base);
  vector_push(factor->base, next_prime);
  factor->min_number = factor->max_number + 1;
  factor->max_number *= 2;
  return;
}

int index_below_n (vector* primes, int n) {
  assert(vector_element(primes, 0) <= n);

  int min = 0;
  int max = primes->length;

  while (max - min > 1) {
    int middle = ((max - min) / 2) + min;
    int middle_value = vector_element(primes, middle);

    if (n >= middle_value) {
      min = middle;
    }
    if (n <= middle_value) {
      max = middle;
    }
  }

  return min;
}

vector* primes_below_n (wheel* factor, int n) {
  // Ensure that there are enough primes to reach n
  while (n > vector_element(factor->primes, factor->primes->length - 1)) {
    wheel_turn(factor);
  }

  int length = index_below_n(factor->primes, n) + 1;

  vector* out = malloc(sizeof(vector));
  out->contents = factor->primes->contents;
  out->size = factor->primes->size;
  out->length = length;
  return out;
}
