#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


//  If p is the perimeter of a right angle triangle with integral length sides, { a, b, c }, there are exactly three solutions for p = 120.
//
//      {20, 48, 52}, { 24, 45, 51 }, { 30, 40, 50 }
//
// For which value of p ≤ 1000, is the number of solutions maximised ?

// Получается система уравнений
// a + b + c = p
// a^2 + b^2 = c^2
//
// a^2 + b^2 - (p - a - b)^2 = 0
// b = p*(p - 2*a) / 2(p - a)

// Условие на периметр c 'Task39 Thread':
//If both a and b are even, c will also be even and P(the perimeter) will be even.
//If both a and b are odd, c will be even and P will be even.
//If one is even and the other is odd, c will be odd and P will again be even.
//Therefore, only even values of P need to be checked.

int main(int argc, char **argv)
{
    size_t perimeter_limit = 1000;

    size_t* perimeters = (size_t*)malloc(perimeter_limit * sizeof(size_t));
    memset(perimeters, 0, perimeter_limit * sizeof(size_t));

    // Method 1: Triplets searching

    printf("\nSearching:\n");

    for (size_t p = 12; p <= perimeter_limit; p += 2)
    {
        for (size_t a = 1; a <= (p - 1) / 3; ++a)
        {
            if (p * (p - 2 * a) / (2 * (p - a)) <= a)
                break;

            if (p * (p - 2 * a) % (2 * (p - a)) == 0)
                perimeters[p - 1]++;
        }
    }

    size_t max_count = 0;
    size_t max_perimeter = 0;

    for (size_t i = 0; i < perimeter_limit; ++i)
    {
        if (perimeters[i] > max_count)
        {
            max_perimeter = i + 1;
            max_count = perimeters[i];
        }
    }

    printf("\tPerimeter(%Iu): %Iu\n", max_count, max_perimeter);

    // Method 2: Triplets generation
    //
    // a = k * (m^2 - n^2)
    // b = k * 2mn 
    // c = k * (m^2 + n^2)
    //
    // a + c < p
    // 2m^2 < p
    // m < sqrt(p/2)
    
    printf("\nGeneration:\n");

    max_count = 0;
    max_perimeter = 0;

    memset(perimeters, 0, perimeter_limit * sizeof(size_t));

    for (size_t m = 2; m < sqrt(perimeter_limit / 2); ++m)
    {
        for (size_t n = m % 2 ? 2 : 1; n < m; n += 2)
        {
            if (gcd(m, n) != 1)
            {
                continue;
            }

            size_t a = (size_t)pow(m, 2) - (size_t)pow(n, 2);
            size_t b = 2 * m * n;
            size_t c = (size_t)pow(m, 2) + (size_t)pow(n, 2);

#ifdef _DEBUG
            printf("%Iu %Iu %Iu\n", a, b, c);
#endif

            // perimeter = k * 2m(m+n)
            for (size_t k = 1; k * 2 * m * (m + n) <= perimeter_limit; ++k)
            {
                perimeters[k * (a + b + c) - 1]++;
            }
        }
    }

    for (size_t i = 0; i < perimeter_limit; ++i)
    {
        if (perimeters[i] > max_count)
        {
            max_perimeter = i + 1;
            max_count = perimeters[i];
        }
    }

    printf("\tPerimeter(%Iu): %Iu\n", max_count, max_perimeter);

    free(perimeters);

    return 0;
}
