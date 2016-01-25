#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The prime 41, can be written as the sum of six consecutive primes :
//      
//      41 = 2 + 3 + 5 + 7 + 11 + 13
//
// This is the longest sum of consecutive primes that adds to a prime below one - hundred.
//
// The longest sum of consecutive primes below one - thousand that adds to a prime, contains 21 terms, and is equal to 953.
//
// Which prime, below one-million, can be written as the sum of the most consecutive primes ?

int main(int argc, char **argv)
{
#ifdef _WIN64
    size_t max_sum_size = 0;
    size_t max_sum = 0;

    size_t upper_bound = 1000000;

    //Получаем последовательные суммы простых чисел
    size_t  sum_size = 1;
    size_t* sum = (size_t*)malloc(sizeof(size_t) * sum_size);
    sum[0] = 2;

    for (size_t n = 3; n < upper_bound; n += 2)
    {
        if (!test_prime(n))
            continue;

        sum_size++;
        sum = (size_t*)realloc(sum, sum_size * sizeof(size_t));
        sum[sum_size - 1] = n + sum[sum_size - 2];

        if (test_prime(sum[sum_size - 1]))
        {
            max_sum = sum[sum_size - 1];
            max_sum_size = sum_size;
        }

        //Проверяем все суммы начинающиеся не с 2
        for (size_t i = sum_size - 1; i > max_sum_size; --i)
        {
            for (size_t j = 1;; ++j)
            {
                size_t current_sum = sum[i] - sum[i - max_sum_size - j];

                if (current_sum > upper_bound)
                    break;

                if (test_prime(current_sum))
                {
                    max_sum = current_sum;
                    max_sum_size = max_sum_size + j;
                }
            }
        }

        //Дальше все последовательные суммы длинее max_sum_size будут привышать 1 миллион
        if (sum_size > max_sum_size)
            if (sum[sum_size - 1] - sum[sum_size - 1 - max_sum_size] > upper_bound)
                break;
    }

    printf("\nResult(%Iu): %Iu\n", max_sum_size, max_sum);
#endif

    return 0;
}
