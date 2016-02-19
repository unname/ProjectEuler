#include <stdlib.h>
#include <Windows.h>
#include <iostream>

#include "euler_functions.h"

// The square root of 2 can be written as an infinite continued fraction.
//
//          √2 = 1 + (1 / 2 + (1 / 2 + (1 / 2 + ...)))
//
// The infinite continued fraction can be written, √2 = [1;(2)],
// (2) indicates that 2 repeats ad infinitum. In a similar way, √23 = [4;(1,3,1,8)].
//
// It turns out that the sequence of partial values of continued fractions for square roots
// provide the best rational approximations. Let us consider the convergents for √2.
//
//
//          another division ladder (-___-)
//          look up "Task57" for it.
//
//
// Hence the sequence of the first ten convergents for √2 are:
//
//      1, 3/2, 7/5, 17/12, 41/29, 99/70, 239/169, 577/408, 1393/985, 3363/2378, ...
//
// What is most surprising is that the important mathematical constant,
//
//      e = [2; 1,2,1,  1,4,1,  1,6,1, ...,  1,2k,1,  ...].
//
// The first ten terms in the sequence of convergents for e are :
//
//      2, 3, 8/3, 11/4, 19/7, 87/32, 106/39, 193/71, 1264/465, 1457/536, ...
//
// The sum of digits in the numerator of the 10th convergent is 1 + 4 + 5 + 7 = 17.
//
// Find the sum of digits in the numerator of the 100th convergent of the continued fraction for e.


int main(int argc, char **argv)
{
    size_t upper_limit = 100 - 1;
    size_t result = 0;

    char* numerator = (char*)malloc(sizeof(char) * 2);
    sprintf_s(numerator, 2, "%Iu", 1);

    size_t a_start = 1;

    if (upper_limit % 3 == 2)
        a_start = 2 * (upper_limit / 3 + 1);

    char* denominator = (char*)malloc(sizeof(char) * (get_digitsize(a_start) + 1));
    sprintf_s(denominator, get_digitsize(a_start) + 1, "%Iu", a_start);

    for (size_t i = upper_limit; i > 0; --i)
    {
        size_t length = 0;

        size_t a_coeff = 1;

        if (i % 3 == 0)
            a_coeff = 2 * (i / 3);
        
        if (i == 1)
            a_coeff = 2;
           
        //numerator += denominator;
        for (size_t k = 0; k < a_coeff; ++k)
        {
            sum_string(numerator, denominator, NULL, &length);
            numerator = (char*)realloc(numerator, sizeof(char) * length);
            sum_string(numerator, denominator, numerator, &length);
        }

        //size_t n = numerator;
        //numerator = denominator;
        //denominator = n;
        char* tmp = (char*)malloc(sizeof(char) * (strlen(numerator) + 1));
        strcpy_s(tmp, strlen(numerator) + 1, numerator);

        numerator = (char*)realloc(numerator, sizeof(char) * (strlen(denominator) + 1));
        strcpy_s(numerator, strlen(denominator) + 1, denominator);

        denominator = (char*)realloc(denominator, sizeof(char) * (strlen(tmp) + 1));
        strcpy_s(denominator, strlen(tmp) + 1, tmp);

        free(tmp);
    }

    for (size_t s = 0; s < strlen(denominator); ++s)
        result += denominator[s] - '0';

    printf("\nResult: %Iu\n", result);

    free(numerator);
    free(denominator);

    return 0;
}
