#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// Consider the fraction, n/d, where n and d are positive integers.If n<d and HCF(n, d) = 1, it is called a reduced proper fraction.
//
// If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get :
//
//          1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
//
// It can be seen that 2/5 is the fraction immediately to the left of 3/7.
//
// By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order of size, find the numerator of the fraction immediately to the left of 3/7.

int main(int argc, char **argv)
{
    // Solved by "Farey sequence"

    size_t upper_limit = 1000000;

    size_t max_fraction_n   = 3;
    size_t max_fraction_d   = 7;

    size_t left_fraction_n  = 2;
    size_t left_fraction_d  = 5;

    while (left_fraction_d + max_fraction_d <= upper_limit)
    {
        left_fraction_n += max_fraction_n;
        left_fraction_d += max_fraction_d;

#ifdef _DEBUG
        printf("\r %Iu / %Iu", left_fraction_n, left_fraction_d);
#endif
    }

    printf("\n\nResult: %Iu\n", left_fraction_n);

    return 0;
}