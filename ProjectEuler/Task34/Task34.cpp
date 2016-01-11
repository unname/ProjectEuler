#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// 145 is a curious number, as 1!+ 4!+ 5! = 1 + 24 + 120 = 145.
//
// Find the sum of all numbers which are equal to the sum of the factorial of their digits.
//
// Note: as 1!= 1 and 2!= 2 are not sums they are not included.

int main(int argc, char **argv)
{
    size_t factorials[] =
    {
        1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880
    };

    size_t result = 0;

    for (size_t i = 10; i < 362880 * 7; ++i)
    {
        size_t n = i;
        size_t sum = 0;
        while (n)
        {
            sum += factorials[n % 10];
            n /= 10;
        }

        if (sum == i)
        {
#ifdef _DEBUG
            printf("%Iu\n", i);
#endif
            result += i;
        }
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}
