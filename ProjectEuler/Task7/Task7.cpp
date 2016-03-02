#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// By listing the first six prime numbers : 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
//
// What is the 10 001st prime number ?

int main(int argc, char **argv)
{
#ifdef _WIN64
    size_t i = 1;
    size_t number = 3;

    while (i < 1000000)
    {
        if (test_prime(number))
        {
            i++;
            if (i == 10001)
                printf("\n%Iu prime is: %Iu\n",i, number);
        }

        number += 2;
    }

    printf("\n%Iu prime is: %Iu\n", i, number - 2);
#endif
    return 0;
}