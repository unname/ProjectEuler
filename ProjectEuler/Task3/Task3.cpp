#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The prime factors of 13195 are 5, 7, 13 and 29.
//
// What is the largest prime factor of the number 600 851 475 143 ?

int main(int argc, char **argv)
{
#ifdef _WIN64
    size_t test_value   = 600851475143;
    size_t max_prime    = 0;

    for (size_t i = 2; i <= sqrt((double)test_value); ++i)
    {
        if (test_value%i == 0)
        {
            if (test_prime(i))
                max_prime = i;
        }
    }

    printf("\nMax prime = %Iu\n", max_prime);
#endif
    return 0;
}