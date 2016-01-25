#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
//
// Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.

bool compare_digits(size_t* digits, size_t size, size_t n)
{
    bool result = false;

    if (get_digitsize(n) != size)
        return result;

    size_t* n_digits = (size_t*)malloc(sizeof(size_t) * size);

    for (size_t i = 0; i < size; ++i)
    {
        n_digits[i] = n / (size_t)pow(10, i) % 10;
    }

    sort(n_digits, size);

    if (!memcmp(digits, n_digits, size * sizeof(size_t)))
        result = true;

    free(n_digits);

    return result;
}

int main(int argc, char **argv)
{
    size_t min_multiplier = 2;
    size_t max_multiplier = 6;

    for (size_t n = 1; ; ++n)
    {
        size_t size = get_digitsize(n);
        size_t* digits = (size_t*)malloc(sizeof(size_t) * size);

        for (size_t i = 0; i < size; ++i)
        {
            digits[i] = n / (size_t)pow(10, i) % 10;
        }

        sort(digits, size);

        for (size_t i = min_multiplier; i <= max_multiplier; ++i)
        {
            if (!compare_digits(digits, size, n * i))
                break;
            
            if (i == max_multiplier)
            {
                printf("\nResult: %Iu\n", n);
                free(digits);
                return 0;
            }
        }

        free(digits);
    }

    return 0;
}
