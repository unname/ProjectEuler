#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// It is well known that if the square root of a natural number is not an integer, then it is irrational.
// The decimal expansion of such square roots is infinite without any repeating pattern at all.
//
// The square root of two is 1.41421356237309504880..., and the digital sum of the first one hundred decimal digits is 475.
//
// For the first one hundred natural numbers, find the total of the digital sums of the first one hundred decimal digits for all the irrational square roots.

int main(int argc, char **argv)
{
    size_t max_n = 100;
    size_t required_precision = 100;

    size_t result_sum = 0;

    for (size_t n = 2; n <= max_n; ++n)
    {
        size_t sqrt_n = sqrt(n);

        if (sqrt_n * sqrt_n == n)
            continue;
        
#ifdef _DEBUG
        printf("sqrt(%Iu) = ", n);
#endif

        size_t num_size = 0;
        size_t den_size = 0;

        char* prev_denominator = nullptr;

        for (size_t approx_degree = 1;; ++approx_degree)
        {
            get_convergent(n, approx_degree, nullptr, &num_size, nullptr, &den_size);
            char* numerator = (char*)malloc(sizeof(char) * num_size);
            char* denominator = (char*)malloc(sizeof(char) * den_size);
            get_convergent(n, approx_degree, numerator, &num_size, denominator, &den_size);

            if (approx_degree > 1)
            {
                size_t precision = 0;

                mult_string(prev_denominator, denominator, nullptr, &precision);

                if (precision - 1 - get_digitsize(sqrt_n) > required_precision)
                {
#ifdef _DEBUG
                    printf("%s / %s = ", numerator, denominator);
#endif
                    numerator = (char*)realloc(numerator, sizeof(char) * (num_size + 1));

                    size_t local_sum = 0;

                    for (size_t i = 0; i < required_precision; ++i)
                    {
                        local_sum = 0;

                        //Делим разряд
                        while (strlen(numerator) > strlen(denominator) || strlen(numerator) == strlen(denominator) && strcmp(numerator, denominator) > 0)
                        {
                            size_t size = 0;
                            sub_string(numerator, denominator, numerator, &size);

                            local_sum++;
                            result_sum++;
                        }
                        //Выводим разряд
#ifdef _DEBUG
                        printf("%Iu", local_sum);
                        if (i == get_digitsize(sqrt_n) - 1)
                            printf(".");
#endif
                        //Увеличиваем разряд
                        for (size_t k = 0; (strlen(numerator) < strlen(denominator) || strlen(numerator) == strlen(denominator) && strcmp(numerator, denominator) < 0); ++k)
                        {
                            if (k > 0)
                            {
#ifdef _DEBUG
                                printf("0");
#endif
                                i++;
                            }

                            numerator[strlen(numerator) + 1] = '\0';
                            numerator[strlen(numerator)] = '0';
                        }
                    }
#ifdef _DEBUG
                    printf("\n");
#endif
                    break;
                }
            }
            
            prev_denominator = (char*)realloc(prev_denominator, (sizeof(char) * den_size));
            strcpy_s(prev_denominator, den_size, denominator);

            free(numerator);
            free(denominator);
        }

        if (prev_denominator)
            free(prev_denominator);
    }

    printf("\nResult: %Iu\n", result_sum);

    return 0;
}