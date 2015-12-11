#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down,
// there are exactly 6 routes to the bottom right corner.
//
// How many such routes are there through a 20×20 grid ?

int main(int argc, char **argv)
{
#ifdef _WIN64
    //size_t n = 16;
    //size_t res = 0;

    //printf("\n");

    //for (size_t i = 0; i < n; ++i)
    //{
    //    res += binom_coeff(n - 1 + i, i);

    //    printf("%Iu + ", binom_coeff(n - 1 + i, i));
    //}

    //res *= 2;

    //printf("\n\nResult: %Iu\n", res);
#endif


    size_t size = 0;
    get_divisor_by_dividend_prime(1404, NULL, &size);

    size_t** arr = (size_t**)malloc(sizeof(size_t*) * size);
    for (size_t i = 0; i < size; ++i)
        arr[i] = (size_t*)malloc(sizeof(size_t) * 2);

    get_divisor_by_dividend_prime(1404, arr, &size);

    for (size_t i = 0; i < size; ++i)
        free(arr[i]);
    free(arr);

    return 0;
}
