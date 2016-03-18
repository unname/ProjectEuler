#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// It turns out that 12 cm is the smallest length of wire that can be bent to form an integer sided right angle triangle in exactly one way, but there are many more examples.
//
//      12 cm: (3, 4, 5)
//      24 cm : (6, 8, 10)
//      30 cm : (5, 12, 13)
//      36 cm : (9, 12, 15)
//      40 cm : (8, 15, 17)
//      48 cm : (12, 16, 20)
//
// In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer sided right angle triangle, and other lengths allow more than one solution to be found; 
// for example, using 120 cm it is possible to form exactly three different integer sided right angle triangles.
//
//      120 cm: (30, 40, 50), (20, 48, 52), (24, 45, 51)
//
// Given that L is the length of the wire, for how many values of L ≤ 1,500,000 can exactly one integer sided right angle triangle be formed ?

int main(int argc, char **argv)
{
    size_t p_min = 12;
    size_t p_max = 1500000;

    size_t result = 0;
    
    //From Task39:  perimeter = k * 2m(m+n)

    for (size_t p = p_min / 2; p <= p_max / 2; ++p)
    {
        size_t triangles_count = 0;

        for (size_t i = 1; i <= sqrt(p); ++i)
        {
            if (p % i == 0)
            {
                for (size_t j = 0; j < 2; ++j)
                {
                    size_t k = i;
                    size_t product = p / k;

                    if (j == 1)
                    {
                        size_t tmp = 0;
                        tmp = k;
                        k = product;
                        product = tmp;

                        if (k == product)
                            continue;
                    }

                    if (product < 6)
                        continue;

                    size_t m_limit = sqrt(product);

                    for (size_t m = m_limit; m >= 2; --m)
                    {
                        if (product % m == 0)
                        {
                            size_t n = product / m - m;

                            if (n >= m)
                                break;

                            if (n >= 1 && (m - n) % 2 == 1 && gcd(m, n) == 1)
                                 triangles_count++;

                            if (triangles_count > 1)
                                goto next_p;
                        }
                    }
                }
            }
        }

        if (triangles_count == 1)
            result++;

    next_p:;
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}