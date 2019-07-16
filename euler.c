#include <stdio.h>
#include <math.h>

typedef struct pair pair;
struct pair {
  int car;
  int cdr;
};

typedef struct vector vector;
struct vector {
  
};

typedef struct factor_environment factor_environment;
struct factor_environment {
  int* base;
  int* current_row;
  int* primes;
  int row_number;
  int max_prime;
};

factor_environment* wheel_factor_init() {
  factor_environment wheel;
  wheel->base = vector_init();
}


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

void print_dims (int triangular_index) {
  pair dims = triangular_dimensions(triangular_index);
  printf("Dims of tri-%d = %d: %dx%d\n", triangular_index, triangular(triangular_index), dims.car, dims.cdr);
  return;
}

int main(int argc, char* argv[]) {
  for (int i = 0; i <= 15; i++) {
    print_dims(i);
  }
  return 0;
}
