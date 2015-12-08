#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
//
// Find the sum of all the primes below two million.

int main(int argc, char **argv)
{
#ifdef _WIN64
    size_t sum = 0;

    for (size_t i = 2; i < 2000000; ++i)
    {
        if (test_prime(i))
            sum += i;
    }

    printf("\nSum = %Iu\n", sum);
#endif
    return 0;
}