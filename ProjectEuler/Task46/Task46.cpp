#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.
//
//  9  = 7  + 2 × 1^2
//  15 = 7  + 2 × 2^2
//  21 = 3  + 2 × 3^2
//  25 = 7  + 2 × 3^2
//  27 = 19 + 2 × 2^2
//  33 = 31 + 2 × 1^2
//
//It turns out that the conjecture was false.
//
//What is the smallest odd composite that cannot be written as the sum of a prime and twice a square ?

int main(int argc, char **argv)
{
    for (size_t n = 9; ; n += 2)
    {
        if (test_prime(n))
            continue;

        size_t correct_sum = false;

        for (size_t k = 1; ; ++k)
        {
            size_t e = 2 * k* k;

            if (e > n)
                break;

            if (test_prime(n - e))
            {
                correct_sum = true;

#ifdef _DEBUG
                printf("%Iu = %Iu + 2 x %Iu^2\n", n, n - e, k);
#endif
            }
        }

        if (!correct_sum)
        {
            printf("\nResult: %Iu\n", n);
            break;
        }
    }
    
    return 0;
}
