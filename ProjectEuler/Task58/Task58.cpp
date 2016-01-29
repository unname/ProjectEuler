#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
//
//          37 36 35 34 33 32 31
//          38 17 16 15 14 13 30
//          39 18  5  4  3 12 29
//          40 19  6  1  2 11 28
//          41 20  7  8  9 10 27
//          42 21 22 23 24 25 26
//          43 44 45 46 47 48 49
//
// It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting
// is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8 / 13 ≈ 62% .
//
// If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed.
// If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10% ?

int main(int argc, char **argv)
{
    size_t prime_count = 0;
    size_t num_count = 1;

    for (size_t i = 3; ; i += 2)
    {
        for (size_t n = 1; n <= 4; ++n)
        {
            if (test_prime((i - 2)*(i - 2) + (n * (i - 1))))
                prime_count++;
        }

        if ((prime_count * 100) / (2 * i - 1) < 10)
        {
            printf("\nResult: %Iu\n", i);
            break;
        }
    }

    return 0;
}