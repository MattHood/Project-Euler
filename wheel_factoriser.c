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

int vector_element (vector vec, int index) {
  if (index < vec.length) {
    return vec.contents[index];
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
  return;
}


typedef struct wheel wheel;
struct wheel {
  vector base;
  vector primes;
  int max_number;
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

void push_if_coprime ();


int main (int argc, char* argv[]) {
  vector* vec = vector_init(1);
  int tarray[] = {2,3,5,7};
  vector_push_array(vec, tarray, 4);
  int* tr = range_array(8, 15);
  vector_push_array(vec, tr, 15-8);
  print_vector(*vec);
  

  return 0;
}


