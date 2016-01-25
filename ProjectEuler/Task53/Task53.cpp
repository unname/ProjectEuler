#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// There are exactly ten ways of selecting three from five, 12345:
//
//      123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
//
// In combinatorics, we use the notation, C(5 3) = 10.
//
// In general,
//
//       C(n r) = n! / r!(n−r)!  
//                              where r ≤ n, n!= n×(n−1)×...×3×2×1, and 0!= 1.
//
// It is not until n = 23, that a value exceeds one-million: C(23 10) = 1144066.
//
// How many, not necessarily distinct, values of C(n r), for 1 ≤ n ≤ 100, are greater than one-million ?

int main(int argc, char **argv)
{
    size_t result = 0;
    size_t lower_limit = 1000000;

    for (size_t n = 1; n <= 100; ++n)
    {
        for (size_t k = 1; k <= n; ++k)
        {
            if (binom_coeff(n, k) > lower_limit)
            {
                result += n - 2 * k + 1;
                break;
            }
        }
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}
