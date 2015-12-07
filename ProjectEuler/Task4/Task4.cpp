#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// A palindromic number reads the same both ways.The largest palindrome made from the product of two 2 - digit numbers is 9009 = 91 × 99.
//
// Find the largest palindrome made from the product of two 3 - digit numbers.

// TODO: think about optimization: https://projecteuler.net/thread=4&page=9#227033

int main(int argc, char **argv)
{
    size_t Pol = 0;

    for (size_t i = 999; i >= 100; --i)
        for (size_t j = 999; j >= 100; --j)
            if (test_palindrome(i*j, 10))
                if (j*i > Pol)
                    Pol = i*j;

    printf("Palindrom = %u", Pol);

    return 0;
}