#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The sum of the squares of the first ten natural numbers is,
// 1^2 + 2^2 + ... + 10^2 = 385
//
// The square of the sum of the first ten natural numbers is,
// (1 + 2 + ... + 10)^2 = 55^2 = 3025
//
// Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
//
// Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

int main(int argc, char **argv)
{
    size_t sum1 = 0;
    size_t sum2 = 0;

    for (size_t i = 1; i <= 100; ++i)
    {
        sum1 += i*i;
        sum2 += i;
    }

    sum2 = pow(sum2, 2);

    printf("\nDifference = %Iu\n", sum2 - sum1);

    return 0;
}