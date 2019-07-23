#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct vector vector;
struct vector {
  int* contents;
  int length;
  int size;
};

vector* vector_init(int length) {
  vector* out = malloc(sizeof(vector));
  out->contents = malloc(sizeof(int) * length);
  for (int i = 0; i < length; i++) {
    out->contents[i] = 0;
  }
  out->length = 0;
  out->size = length;
  return out;
}

int vector_element (vector* vec, int index) {
  if (index < vec->length) {
    return vec->contents[index];
  }
  else {
    return -1;
  }
}

void vector_double (vector* vec) {
  int old_size = vec->size;
  vec->contents = realloc(vec->contents, 2 * old_size * sizeof(int));
  vec->size = 2 * old_size;
  for (int i = old_size; i < 2 * old_size; i++) {
    vec->contents[i] = 0;
  }
  return;
}

void vector_push (vector* vec, int el) {
  if (vec->length + 1 >= vec->size) {
    vector_double(vec);
  }
  vec->contents[vec->length] = el;
  vec->length++;
  return;
}
void vector_push_array (vector* vec, int array[], int array_length) {
  for (int i = 0; i < array_length; i++) {
    vector_push(vec, array[i]);
  }
  return;
}

void print_vector (vector vec) {
  for (int i = 0; i < vec.length; i++) {
    printf("[%d]: %d ", i, vec.contents[i]);
  }
  printf("\n");
  return;
}


typedef struct wheel wheel;
struct wheel {
  vector* base;
  vector* primes;
  int max_number;
  int min_number;
  int next_base;
};

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
  factor->max_number *= next_prime;
  return;
}

vector* primes_below_n (wheel* factor, int n) {
  vector* out_vector = vector_init(1);
  _Bool exceeded = 0;
  for (int i = 0; !exceeded; i++) {
    if (i >= factor->primes->length) {
      wheel_turn(factor);
    }
    int prime = vector_element(factor->primes, i);
    if (prime < n) {
      vector_push(out_vector, prime);
    }
    else {
      exceeded = 1;
    }
  }
  return out_vector;
}

int main (int argc, char* argv[]) {
  wheel* factor = wheel_init();
  print_vector(*primes_below_n(factor, 200));
  print_vector(*factor->base);
 
  return 0;
 }


