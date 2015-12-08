#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
//
//     a^2 + b^2 = c^2
//
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
//
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.

int main(int argc, char **argv)
{
    size_t sum = 1000;

    for (size_t a = 1; a < sum / 3; ++a)
        for (size_t b = 1; b <= (sum-1)/2; ++b)
            if (a*a + b*b == (sum - a - b)*(sum - a - b))
            {
                printf("\nA = %Iu\nB = %Iu\nC = %Iu\n",a ,b, sum-a-b);
                printf("\nProduct = %Iu\n", a*b*(sum - a - b));
                goto end;
            }
end:
    return 0;
}