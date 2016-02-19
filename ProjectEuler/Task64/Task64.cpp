#include <stdlib.h>
#include <Windows.h>
#include <iostream>

#include "euler_functions.h"


// All square roots are periodic when written as continued fractions and can be written in the form :
//
//          √N = a0 + (1 / a1 + (1 / a2 + (1 / a3 + ...)))
//
// For example, let us consider √23:
//
//          √23 = 4 + √23 — 4 = 4 + 1 / (1 / √23 — 4) = 4 + 1 / (1 + √23 — 3 / 7)
//
// If we continue we would get the following expansion:
//
//          √23 = 4 + (1 / 1 + (1 / 3 + (1 / 1 + (1 / 8 + ...))))
// 
// The process can be summarised as follows:
//
//      a0 = 4,     1 / √23 - 4 = √23 + 4 / 7 = 1 + √23 - 3 / 7
//      a1 = 1,     7 / √23 - 3 = 7(√23 + 3) / 14 = 3 + √23 - 3 / 2 
//      a2 = 3,     2 / √23 - 3 = 2(√23 + 3) / 14 = 1 + √23 - 4 / 7
//      a3 = 1,     7 / √23 - 4 = 7(√23 + 4) / 7 = 8 + √23 - 4
//      a4 = 8,     1 / √23 - 4 = ....
//
// It can be seen that the sequence is repeating. For conciseness, we use the notation √23 = [4;(1,3,1,8)],
// to indicate that the block (1,3,1,8) repeats indefinitely.
//
// The first ten continued fraction representations of (irrational) square roots are:
//      √2  = [1; (2)], period = 1
//      √3  = [1; (1, 2)], period = 2
//      √5  = [2; (4)], period = 1
//      √6  = [2; (2, 4)], period = 2
//      √7  = [2; (1, 1, 1, 4)], period = 4
//      √8  = [2; (1, 4)], period = 2
//      √10 = [3; (6)], period = 1
//      √11 = [3; (3, 6)], period = 2
//      √12 = [3; (2, 6)], period = 2
//      √13 = [3; (1, 1, 1, 1, 6)], period = 5
//
// Exactly four continued fractions, for N ≤ 13, have an odd period.
//
// How many continued fractions for N ≤ 10000 have an odd period ?

int main(int argc, char **argv)
{
    size_t number_limit = 10000;
 
    size_t result = 0;

    for (size_t number = 2; number <= number_limit; ++number)
    {
        size_t n_sqr = (size_t)sqrt(number);

        if (n_sqr * n_sqr == number)
            continue;

        int numerator_c = 1;
        int denominator_c = n_sqr;
        size_t a_coeff = 1;

        size_t period_length = 0;
#ifdef _DEBUG
        printf(" sqr(%Iu) = [%Iu; (", number, n_sqr);
#endif
        do
        {
            period_length++;

            numerator_c = (number - denominator_c * denominator_c) / numerator_c;
                
            a_coeff = (n_sqr + denominator_c) / numerator_c;
#ifdef _DEBUG
            printf("%Iu, ", a_coeff);
#endif
            denominator_c = numerator_c * a_coeff - denominator_c;

        } while (numerator_c != 1 || denominator_c != n_sqr);

#ifdef _DEBUG
        printf(")]\n");
#endif
        if (period_length % 2)
            result++;
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}