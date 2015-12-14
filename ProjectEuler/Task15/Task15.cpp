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
    size_t n      = 20;
    size_t res    = 0;
    size_t binom  = 0;

    printf("\n");

    for (size_t i = 0; i < n; ++i)
    {
        binom = binom_coeff(n - 1 + i, i);
        res += binom;
#ifdef _DEBUG
        printf("%Iu + ", binom);
#endif
    }

    res *= 2;

    printf("\n\nResult: %Iu\n", res);


    //Решение сообщества ProjectEuler:
    printf("\n\nResult(by community): %Iu\n", binom_coeff(2* n, n));

#endif
    return 0;
}
