#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits :
//
//      1634 = 1^4 + 6^4 + 3^4 + 4^4
//      8208 = 8^4 + 2^4 + 0^4 + 8^4
//      9474 = 9^4 + 4^4 + 7^4 + 4^4
//
// As 1 = 1^4 is not a sum it is not included.
//
// The sum of these numbers is 1634 + 8208 + 9474 = 19316.
//
// Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

int main(int argc, char **argv)
{
    size_t power = 5;
    size_t result = 0;

    for (size_t n = 2; n < (power + 1) * pow(9, power); ++n)
    {
        size_t sum = 0;
        size_t n1 = n;

        while (n1)
        {
            sum += pow(n1 % 10, power);
            n1 /= 10;
        }

        if (n == sum)
        {
            result += n;

#ifdef _DEBUG
            printf("%Iu\n", n);
#endif
        }
    }

    printf("\n%Result: %Iu\n", result);

    return 0;
}