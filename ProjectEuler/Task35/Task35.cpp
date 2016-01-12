#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The number, 197, is called a circular prime because all rotations of the digits : 197, 971, and 719, are themselves prime.
//
// There are thirteen such primes below 100 : 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
//
// How many circular primes are there below one million ?

int main(int argc, char **argv)
{
#ifdef _WIN64
    size_t result = 0;
    size_t upper_limit = 1000000;

    for (size_t i = 1; i < upper_limit; ++i)
    {
        size_t n = i;
        size_t size = get_digitsize(n);

        if (size > 1)
        {
            while (n)
            {
                if (n % 10 % 2 == 0 || n % 10 == 5)
                    goto end;

                n /= 10;
            }

            n = i;
        }

        if (!test_prime(n))
            goto end;

        for (size_t j = 1; j < size; ++j)
        {
            n = (n * 10 + n / (size_t)pow(10, size - 1)) % (size_t)pow(10, size);

            if (!test_prime(n))
                goto end;
        }

        result++;

#ifdef _DEBUG
        printf("%Iu\n", i);
#endif

    end:;
    }

    printf("\nResult: %Iu\n", result);
#endif

    return 0;
}
