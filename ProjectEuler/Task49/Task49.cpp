#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways :
//
// (i) each of the three terms are prime, and,
// (ii)each of the 4-digit numbers are permutations of one another.
//
// There are no arithmetic sequences made up of three 1-,2-, or 3-digit primes, 
// exhibiting this property, but there is one other 4-digit increasing sequence.
//
// What 12-digit number do you form by concatenating the three terms in this sequence ?

int main(int argc, char **argv)
{
    const size_t digit_size = 4;

    for (size_t n = pow(10, digit_size - 1) + 1; n < pow(10, digit_size); n += 2)
    {
        if (n % 5 == 0 || n == 1487)
            continue;

        if (!test_prime(n))
            continue;

        //»щем все возможные простые перестановки больше n
        size_t digits[digit_size];

        for (size_t i = 0, n1 = n; i < digit_size; ++i)
        {
            digits[i] = n1 % 10;
            n1 /= 10;
        }

        sort(digits, digit_size);

        size_t size = 0;
        size_t* permutations = nullptr;

        for (size_t i = factorial(digit_size) - 1; ; --i)
        {
            size_t m = get_lex_permut(digits, digit_size, i);

            if (!test_prime(m))
                continue;

            if (m == n)
                break;
           
            size++;
            permutations = (size_t*)realloc(permutations, size * sizeof(size_t));
            permutations[size - 1] = m;
        }

        //»щем в перестановках арифметическую прогрессию из 3 членов

        if (size < 2)
        {
            free(permutations);
            continue;
        }

        sort(permutations, size);

        for (size_t i = 0; i < size - 1; ++i)
        {
            for (size_t j = i + 1; j < size; ++j)
            {
                if (permutations[i] - n == permutations[j] - permutations[i])
                {
                    printf("\nResult: %Iu%Iu%Iu\n", n, permutations[i], permutations[j]);

                    free(permutations);
                    return 0;
                }
            }
        }

        free(permutations);
    }

    return 0;
}
