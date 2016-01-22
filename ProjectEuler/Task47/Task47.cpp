#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The first two consecutive numbers to have two distinct prime factors are :
//
//      14 = 2 × 7
//      15 = 3 × 5
//
// The first three consecutive numbers to have three distinct prime factors are :
//
//      644 = 2² × 7 × 23
//      645 = 3 × 5 × 43
//      646 = 2 × 17 × 19.
//
// Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers ?

int main(int argc, char **argv)
{
    size_t distinct = 4;
    size_t count = 0;

    for (size_t n = 1;; ++n)
    {
        size_t size = 0;
        get_divisor_by_dividend_prime(n, NULL, &size);

        if (size == distinct)
            count++;
        else
            count = 0;

        if (count == distinct)
        {
            printf("\nResult: %Iu\n", n - 3);
            break;
        }
    }

    return 0;
}
