#include <stdlib.h>
#include <Windows.h>
#include <iostream>

#include "euler_functions.h"


// Consider quadratic Diophantine equations of the form :
//
//                  x^2 – Dy^2 = 1
//
// For example, when D = 13, the minimal solution in x is 649^2 – 13×180^2 = 1.
//
// It can be assumed that there are no solutions in positive integers when D is square.
//
// By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following :
//
//      3^2 – 2 × 2^2 = 1
//      2^2 – 3 × 1^2 = 1
//      9^2 – 5 × 4^2 = 1
//      5^2 – 6 × 2^2 = 1
//      8^2 – 7 × 3^2 = 1
//
// Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D = 5.
//
// Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.

int main(int argc, char **argv)
{
    size_t upper_limit = 1000;

    size_t result = 0;
    char* max_x = (char*)malloc(sizeof(char) * 2);
    sprintf_s(max_x, 2, "%Iu", 0);

    for (size_t d = 2; d <= upper_limit; ++d)
    {
        if ((size_t)sqrt(d) * (size_t)sqrt(d) == d)
            continue;

        size_t fraction_size = 0;

        get_continued_fraction(d, nullptr, &fraction_size);

        size_t approx_degree;

        // Алгоритм выбора степени приблежённой дроби:
        //1) номер преблежённой дроби должен быть нечётен
        //2) номер приблежённой дроби должен удовлетворять условию: approx_degree (mod n) = n - 1
        //3) минимальное решение
        if ((fraction_size - 1) % 2 == 0)
            approx_degree = (fraction_size - 1) - 1;
        else
            approx_degree = 2 * (fraction_size - 1) - 1;

        size_t num_size = 0;
        size_t den_size = 0;

        get_convergent(d, approx_degree, nullptr, &num_size, nullptr, &den_size);
        char* numerator = (char*)malloc(sizeof(char) * num_size);
        char* denominator = (char*)malloc(sizeof(char) * den_size);
        get_convergent(d, approx_degree, numerator, &num_size, denominator, &den_size);

#ifdef _DEBUG
        printf(" %s^2 - %Iu x %s^2 = 1\n", numerator, d, denominator);
#endif

        if (strlen(numerator) > strlen(max_x) ||
            strlen(numerator) == strlen(max_x) &&
            strcmp(numerator, max_x) > 0)
        {
            result = d;
            max_x = (char*)realloc(max_x, sizeof(char) * (num_size));
            strcpy_s(max_x, num_size, numerator);
        }

        free(numerator);
        free(denominator);
    }

    printf("\nResult: %Iu\n", result);

    free(max_x);

    return 0;
}
