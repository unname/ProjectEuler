#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include "euler_functions.h"


// The smallest number expressible as the sum of a prime square, prime cube, and prime fourth power is 28.
// In fact, there are exactly four numbers below fifty that can be expressed in such a way :
//
//      28 = 2^2 + 2^3 + 2^4
//      33 = 3^2 + 2^3 + 2^4
//      49 = 5^2 + 2^3 + 2^4
//      47 = 2^2 + 3^3 + 2^4
//
// How many numbers below fifty million can be expressed as the sum of a prime square, prime cube, and prime fourth power ?

int main(int argc, char **argv)
{
    size_t upper_limit = 50000000;

    size_t limit_2 = pow(upper_limit - 8 - 16, (float) 1 / 2);
    size_t limit_3 = pow(upper_limit - 4 - 16, (float) 1 / 3);
    size_t limit_4 = pow(upper_limit - 4 - 8,  (float) 1 / 4);

    size_t* term_2 = (size_t*)malloc(sizeof(size_t) * 1);
    size_t* term_3 = (size_t*)malloc(sizeof(size_t) * 1);
    size_t* term_4 = (size_t*)malloc(sizeof(size_t) * 1);

    term_2[0] = 2 * 2;
    term_3[0] = term_2[0] * 2;
    term_4[0] = term_3[0] * 2;

    size_t size_2 = 1;
    size_t size_3 = 1;
    size_t size_4 = 1;

    for (size_t n = 3; n <= limit_2; n += 2)
    {
        if (test_prime(n))
        {
            size_2++;

            term_2 = (size_t*)realloc(term_2, sizeof(size_t) * size_2);
            term_2[size_2 - 1] = n * n;

            if (n <= limit_3)
            {
                size_3++;

                term_3 = (size_t*)realloc(term_3, sizeof(size_t) * size_3);
                term_3[size_3 - 1] = term_2[size_3 - 1] * n;

                if (n <= limit_4)
                {
                    size_4++;

                    term_4 = (size_t*)realloc(term_4, sizeof(size_t) * size_4);
                    term_4[size_4 - 1] = term_3[size_4 - 1] * n;
                }
            }
        }
    }

    size_t result = 0;

    for (int i4 = size_4 - 1; i4 >= 0; i4--)
    {
        for (int i3 = size_3 - 1; i3 >= 0; i3--)
        {
            if (term_3[i3] + term_4[i4] >= upper_limit)
                continue;

            for (int i2 = size_2 - 1; i2 >= 0; i2--)
            {
                if (term_2[i2] + term_3[i3] + term_4[i4] < upper_limit)
                {
                    result += i2 + 1;
                    break;
                }
            }
        }
    }

    printf("\nResult: %Iu\n", result);

    free(term_2);
    free(term_3);
    free(term_4);

    return 0;
}