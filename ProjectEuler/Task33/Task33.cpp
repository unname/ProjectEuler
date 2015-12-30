#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The fraction 49 / 98 is a curious fraction, as an inexperienced mathematician in attempting to simplify
// it may incorrectly believe that 49 / 98 = 4 / 8, which is correct, is obtained by cancelling the 9s.
// 
// We shall consider fractions like, 30 / 50 = 3 / 5, to be trivial examples.
// 
// There are exactly four non - trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.
// 
// If the product of these four fractions is given in its lowest common terms, find the value of the denominator.

size_t remove_digit(size_t n, size_t offset)
{
#ifdef _WIN64
    #define MAX_OFFSET 19
#else
    #define MAX_OFFSET 9
#endif

    if (offset > MAX_OFFSET)
        return n;

    return n % (size_t)pow(10, offset) + n / ((size_t)pow(10, offset + 1)) * (size_t)pow(10, offset);
}

int main(int argc, char **argv)
{
    size_t numerator = 1;
    size_t denominator = 1;

    for (size_t a = 11; a < 100; ++a)
    {
        if (a % 10 == 0)
            continue;

        for (size_t b = a + 1; b < 100; ++b)
        {
            if (b % 10 == 0)
                continue;

            size_t a1 = a;
            size_t b1 = b;
            size_t i = 0;
            size_t j = 0;

            while (a1)
            {
                while (b1)
                {
                    if (a1 % 10 == b1 % 10)
                        goto digits_found;

                    b1 /= 10;
                    j++;
                }

                a1 /= 10;
                i++;
            }

digits_found:

            a1 = remove_digit(a, i);
            b1 = remove_digit(b, j);

            if (a * b1 == a1 * b && a != a1)
            {
                numerator *= a;
                denominator *= b;
#ifdef _DEBUG
                printf("%Iu/%Iu = %Iu/%Iu\n", a, b, a1, b1);
#endif
            }
        }
    }

    printf("\nResult: %Iu\n", denominator / gcd(numerator, denominator));

    return 0;
}
