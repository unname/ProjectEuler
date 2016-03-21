#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"

// It is possible to write ten as the sum of primes in exactly five different ways :
//
//      7 + 3
//      5 + 5
//      5 + 3 + 2
//      3 + 3 + 2 + 2
//      2 + 2 + 2 + 2 + 2
//
// What is the first value which can be written as the sum of primes in over five thousand different ways ?

int main(int argc, char **argv)
{
    size_t bottom_bound = 5000;

    size_t  set_size = 0;
    size_t* set = nullptr;

    for (size_t n = 2;; ++n)
    {
        if (test_prime(n))
        {
            set_size++;
            set = (size_t*) realloc(set, sizeof(size_t) * set_size);
            set[set_size - 1] = n;
        }

        if (p(n, set, set_size) > bottom_bound)
        {
            printf("\nResult: %Iu\n", n);
            break;
        }
    }

    if (set)
        free(set);

    return 0;
}