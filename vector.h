#ifndef VECTOR
#define VECTOR

typedef struct vector vector;
struct vector {
  int* contents;
  int length;
  int size;
};

vector* vector_init       (int length);
void    vector_free       (vector* vec);
int     vector_element    (vector* vec, int index);
void    vector_push       (vector* vec, int el);
void    vector_push_array (vector* vec, int array[], int array_length);
void    print_vector      (vector  vec);
int     vector_last       (vector* vec);

#endif
