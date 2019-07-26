#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "vector.h"

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

void vector_free(vector* vec) {
  free(vec->contents);
  free(vec);
  return;
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

int vector_last (vector* vec) {
  return vector_element(vec, vec->length - 1);
}

// Tests

void vector_test_fidelity (vector* vec) {
  int i;
  for (i = 0; i < 40000000; i++) {
    vector_push(vec, i);
    if (i != vector_last(vec)) {
      printf("Failed at %d, got %d\n", i, vector_last(vec));
      break;
    }
  }
  printf("Pushed %d elements\n", i);
}

/*int main (int argc, char* argv[]) {
  vector* vec = vector_init(1);
  vector_test_fidelity(vec);
  return 0;
  }*/
