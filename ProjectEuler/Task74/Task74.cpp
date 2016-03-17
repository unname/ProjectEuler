#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:
//
//      1!+ 4!+ 5!= 1 + 24 + 120 = 145
//
// Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; it turns out that there are only three such loops that exist :
//
//      169 → 363601 → 1454 → 169
//      871 → 45361 → 871
//      872 → 45362 → 872
//
// It is not difficult to prove that EVERY starting number will eventually get stuck in a loop. For example,
//
//      69 → 363600 → 1454 → 169 → 363601 (→ 1454)
//      78 → 45360 → 871 → 45361 (→ 871)
//      540 → 145 (→ 145)
//
// Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with a starting number below one million is sixty terms.
//
// How many chains, with a starting number below one million, contain exactly sixty non-repeating terms ?

int main(int argc, char **argv)
{
    size_t upper_limit = 1000000;
    size_t chain_length = 60;

    size_t factorials[] =
    {
        1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880
    };

    size_t result = 0;

    for (size_t n = 69; n < upper_limit; ++n)
    { 
        size_t factorial_sum = n;
        size_t size = 0;

        while (true)
        {
            switch (factorial_sum)
            {
            case 169:
            case 363601:
            case 1454:
                size += 3;
                goto next_number;
            case 871:
            case 45361:
            case 872:
            case 45362:
                size += 2;
                  goto next_number;
            default:
                break;
            }

            size_t next_sum = 0;
            size_t previous_sum = factorial_sum;

            while (factorial_sum)
            {
                next_sum += factorials[factorial_sum % 10];
                factorial_sum /= 10;
            }

            // avoid instant cycles as 2, 145, 40585
            if (next_sum == previous_sum)
                goto next_number;

            factorial_sum = next_sum;
            size++;
        }

    next_number:
        if (size == chain_length)
            result++;
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}