#ifndef VECTOR_H
#define VECTOR_H

#include "struct.h"

vector_t *create_aligned_vector_float_32(int size);
void set_random_numbers_to_vector(vector_t **vector);
float calculate_scalar_vectors_c(vector_t *vector_1, vector_t *vector_2);
float calculate_scalar_vectors_assembler(vector_t *vector_1, vector_t *vector_2);
float calculate_scalar_vectors_assembler_packed(vector_t *vector_1, vector_t *vector_2);

#endif