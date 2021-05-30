#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#define COUNT_RUNS 1

void sum_float_numbers(float float_number_1, float float_number_2);
void sum_double_numbers(double double_number_1, double double_number_2);
void sum_long_double_numbers(long double long_double_number_1, long double long_double_number_2);
void mul_float_numbers(float float_number_1, float float_number_2);
void mul_double_numbers(double double_number_1, double double_number_2);
void mul_long_double_numbers(long double long_double_number_1, long double long_double_number_2);

void calculate_pi();

int main(void)
{
    float float_number_1 = 50.025, float_number_2 = 23.987;
    double double_number_1 = 50.025, double_number_2 = 23.987;
    //long double long_double_number_1 = 50.025, long_double_number_2 = 23.987;

    printf("Start time researches.\n");
    sum_float_numbers(float_number_1, float_number_2);
    printf("Sum float is done.\n");

    sum_double_numbers(double_number_1, double_number_2);
    printf("Sum double is done.\n");

    //sum_long_double_numbers(long_double_number_1, long_double_number_2);
    //printf("Sum long double is done.\n");

    mul_float_numbers(float_number_1, float_number_2);
    printf("Mul float is done.\n");

    mul_double_numbers(double_number_1, double_number_2);
    printf("Mul double is done.\n");

    //mul_long_double_numbers(long_double_number_1, long_double_number_2);
    //printf("Mul long double is done.\n");

    
    calculate_pi();
    return 0;
}

void sum_float_numbers(float float_number_1, float float_number_2)
{
    float result = 0;
    clock_t start, end;
    double result_time;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        result = float_number_1 + float_number_2;
        end = clock() - start;
        result_time += end;
    }

    result_time = 0;
    double time_option = result_time / COUNT_RUNS;

    printf("Time sum float = %lf\n", time_option);

    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        asm
        (
            "flds %1\n"
            "flds %2\n"
            "faddp\n"
            "fstps %0\n"
            : "=m" (result)
            : "m" (float_number_1), "m" (float_number_2)
        );
        end = clock() - start;
        result_time += end;
    }
    time_option = result_time / COUNT_RUNS;
    printf("Time sum float (asm_insert) = %lf\n\n", time_option);
}

void sum_double_numbers(double double_number_1, double double_number_2)
{
    double result = 0;
    clock_t start, end;
    double result_time;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        result = double_number_1 + double_number_2;
        end = clock() - start;
        result_time += end;
    }

    double time_option = result_time / COUNT_RUNS;
    printf("Time sum double = %lf\n", time_option);

    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        asm(
            "fldl %1\n"
            "fldl %2\n"
            "faddp\n"
            "fstpl %0\n"
            : "=m" (result)
            : "m" (double_number_1), "m" (double_number_2)
        );
        end = clock() - start;
        result_time += end;
    }
    time_option = result_time / COUNT_RUNS;
    printf("Time sum double (asm_insert) = %lf\n\n", time_option);
}

void mul_float_numbers(float float_number_1, float float_number_2)
{
    float result = 0;
    clock_t start, end;
    double result_time;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        result = float_number_1 * float_number_2;
        end = clock() - start;
        result_time += end;
    }

    double time_option = result_time / COUNT_RUNS;
    printf("Time mul float = %lf\n", time_option);

    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        asm(
            "flds %1\n"
            "flds %2\n"
            "fmulp\n"
            "fstps %0\n"
            : "=m" (result)
            : "m" (float_number_1), "m" (float_number_2)
        );
        end = clock() - start;
        result_time += end;
    }
        
    time_option = result_time / COUNT_RUNS;
    printf("Time mul float (asm_insert) = %lf\n\n", time_option);
} 

void mul_double_numbers(double double_number_1, double double_number_2)
{
    double result = 0;
    clock_t start, end;
    double result_time;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        result = double_number_1 * double_number_2;
        end = clock() - start;
        result_time += end;
    }

    double time_option = result_time / COUNT_RUNS;
    printf("Time mul double = %lf\n", time_option);

    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        asm(
            "fldl %1\n"
            "fldl %2\n"
            "fmulp\n"
            "fstpl %0\n"
            : "=m" (result)
            : "m" (double_number_1), "m" (double_number_2)
        );
        end = clock() - start;
        result_time += end;
    }

    time_option = result_time / COUNT_RUNS;
    printf("Time mul double (asm_insert) = %lf\n\n", time_option);
}

void calculate_pi()
{
    double result;
    printf("math sin(3.14) = %lf\n", sin(3.14));
    printf("math sin(3.141596) = %lf\n", sin(3.141596));

    asm
    (
        "fldpi\n"
        "fsin\n"
        "fstpl %0\n"
        : "=m" (result)
    );

    printf("FPU sin(pi) = %lf\n", result);
    printf("math sin(3.14 / 2) = %lf\n", sin(3.14 / 2));
    printf("math sin(3.141596 / 2) = %lf\n", sin(3.141596 / 2));

    asm
    (
        "fld1\n"
        "fld1\n"
        "faddp\n"
        "fldpi\n"
        "fdivp\n"
        "fsin\n"
        "fstpl %0\n"
        : "=m" (result)
    );
    printf("FPU sin(pi / 2) = %f\n", result);
}

/*void sum_long_double_numbers(long double long_double_number_1, long double long_double_number_2)
{
    double result = 0;
    clock_t start, end;
    double result_time;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        result = long_double_number_1 + long_double_number_2;
        end = clock() - start;
        result_time += end;
    }

    double time_option = result_time / COUNT_RUNS;
    printf("Time sum long double = %lf\n", time_option);

    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        asm(
            "fldt %1\n"
            "fldt %2\n"
            "faddp\n"
            "fstpt %0\n"
            : "=m" (result)
            : "m" (long_double_number_1), "m" (long_double_number_2)
        );
        end = clock() - start;
        result_time += end;
    }
    time_option = result_time / COUNT_RUNS;
    printf("Time sum long double (asm_insert) = %lf\n\n", time_option);
}

void mul_long_double_numbers(long double long_double_number_1, long double long_double_number_2)
{
    double result = 0;
    clock_t start, end;
    double result_time;
    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        result = long_double_number_1 * long_double_number_2;
        end = clock() - start;
        result_time += end;
    }

    double time_option = result_time / COUNT_RUNS;
    printf("Time mul double = %lf\n", time_option);

    for (int i = 0; i < COUNT_RUNS; i++)
    {
        start = clock();
        asm(
            "fldt %1\n"
            "fldt %2\n"
            "fmulp\n"
            "fstpt %0\n"
            : "=m" (result)
            : "m" (long_double_number_1), "m" (long_double_number_2)
        );
        end = clock() - start;
        result_time += end;
    }

    time_option = result_time / COUNT_RUNS;
    printf("Time mul double (asm_insert) = %lf\n\n", time_option);
}*/