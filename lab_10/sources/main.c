#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "struct.h"
#include "vector.h"

#define COUNT_RUNS 1e6
#define MAX_RAND 10000

int main(void)
{
    clock_t start_time = 0, end_time = 0;
    double result_time = 0, time_option = 0;
    float sum_result = 0;
    vector_t *vector_1 = create_aligned_vector_float_32(64);
    vector_t *vector_2 = create_aligned_vector_float_32(64);

    set_random_numbers_to_vector(&vector_1);
    set_random_numbers_to_vector(&vector_2);

    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start_time = clock();
        sum_result = calculate_scalar_vectors_c(vector_1, vector_2);
        //printf("Sum_result_c = %lf\n", sum_result);
        end_time = clock() - start_time;
        result_time += end_time;
    }
    time_option = result_time / COUNT_RUNS;
    printf("C run time: %.9lf seconds\n\n", time_option);

    result_time = 0;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start_time = clock();
        sum_result = calculate_scalar_vectors_assembler(vector_1, vector_2);
        //printf("Sum_result_assembler = %lf\n", sum_result);
        end_time = clock() - start_time;
        result_time += end_time;
    }
    time_option = result_time / COUNT_RUNS;
    printf("Assembler run time %.9lf seconds\n\n", time_option);

    result_time = 0;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start_time = clock();
        sum_result = calculate_scalar_vectors_assembler_packed(vector_1, vector_2);
        //printf("Sum_result_assembler = %lf\n", sum_result);
        end_time = clock() - start_time;
        result_time += end_time;
    }
    time_option = result_time / COUNT_RUNS;
    printf("Assembler run time %.9lf seconds\n\n", time_option);

    free(vector_1);
    free(vector_2);

    return 0;
}

vector_t *create_aligned_vector_float_32(int size)
{
    size_t alligment = sizeof(float);
    size_t alligment_size = (size % alligment) ? (size + (alligment - size % alligment)) : size;

    vector_t *vector = calloc(1, sizeof(vector_t) + sizeof(float) * alligment_size);

    if (vector)
        vector->size = alligment_size;

    return vector;
}

void set_random_numbers_to_vector(vector_t **vector)
{
    srand(time(NULL));
    for (int i = 0; i < (*vector)->size; i++)
    {
        (*vector)->vector[i] = (float)(rand() % MAX_RAND);
    }
}

float calculate_scalar_vectors_c(vector_t *vector_1, vector_t *vector_2)
{
    float sum_result = 0, current_value = 0;
    for (int i = 0; i < vector_1->size; i++)
    {
        current_value = vector_1->vector[i] * vector_2->vector[i];
        sum_result += current_value;
    }

    return sum_result;
}

float calculate_scalar_vectors_assembler(vector_t *vector_1, vector_t *vector_2)
{
    float sum_result = 0;

    for (int i = 0; i < vector_1->size; i++)
    {
        __asm__
        (
            "movups (%0), %%xmm0\n\t"
            "movups (%1), %%xmm1\n\t"
            "mulps %%xmm1, %%xmm0\n\t"
            "haddps %%xmm0, %%xmm0\n\t"
            "addss %%xmm0, %%xmm2\n\t"
            :
            : "r" (vector_1->vector + i), "r" (vector_2->vector + i)
        );
    }

    __asm__
    (
        "haddps %%xmm2, %%xmm2\n\t"
        "movss %%xmm2, %0\n\t"
        : "=m"(sum_result)
        :
        : "xmm0", "xmm1", "xmm2"
    );

    return sum_result;
}

float calculate_scalar_vectors_assembler_packed(vector_t *vector_1, vector_t *vector_2)
{
    float sum_result = 0;

    for (int i = 0; i < vector_1->size; i++)
    {
        __asm__
        (
            "movss (%0), %%xmm0\n\t"
            "movss (%1), %%xmm1\n\t"
            "mulps %%xmm1, %%xmm0\n\t"
            //"haddps %%xmm0, %%xmm0\n\t"
            "addss %%xmm0, %%xmm2\n\t"
            :
            : "r" (vector_1->vector + i), "r" (vector_2->vector + i)
            : "xmm0", "xmm1", "xmm2"
        );
    }

    /*__asm__
    (
        "haddps %%xmm2, %%xmm2\n\t"
        "movss %%xmm2, %0\n\t"
        : "=m"(sum_result)
        :
        : "xmm0", "xmm1", "xmm2"
    );*/

    return sum_result;
}