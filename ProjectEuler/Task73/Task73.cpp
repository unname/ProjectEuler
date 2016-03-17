#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// Consider the fraction, n/d, where n and d are positive integers.If n<d and HCF(n,d) = 1, it is called a reduced proper fraction.
//
// If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get :
//
//      1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
//
// It can be seen that there are 3 fractions between 1/3 and 1/2.
//
// How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper fractions for d ≤ 12,000 ?

int main(int argc, char **argv)
{
    size_t d = 12000;

    size_t left_d  = 3;
    size_t right_d = 2;

    size_t right_fraction_n = 1;
    size_t right_fraction_d = left_d;

    size_t left_fraction_n = 0;
    size_t left_fraction_d = 1;

    while (left_fraction_d + right_fraction_d <= d)
    {
        left_fraction_n += right_fraction_n;
        left_fraction_d += right_fraction_d;
    }

#ifdef _DEBUG
    printf("\nFraction the left of %Iu/%Iu:  %Iu/%Iu\n", right_fraction_n, right_fraction_d, left_fraction_n, left_fraction_d);
#endif

    size_t result = 0;

    while (true)
    {
        size_t k = (d + left_fraction_d) / right_fraction_d;

        size_t next_n = k * right_fraction_n - left_fraction_n;
        size_t next_d = k * right_fraction_d - left_fraction_d;

        left_fraction_n = right_fraction_n;
        left_fraction_d = right_fraction_d;

        right_fraction_n = next_n;
        right_fraction_d = next_d;

        if (right_fraction_d != 2)
            result++;
        else
            break;
    }

#ifdef _DEBUG
    printf("Fraction the left of 1/2:  %Iu/%Iu\n", left_fraction_n, left_fraction_d);
#endif

    printf("\nResult: %Iu\n", result);

    return 0;
}