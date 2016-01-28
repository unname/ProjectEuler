#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// A googol(10^100) is a massive number: one followed by one-hundred zeros;
// 100^100 is almost unimaginably large: one followed by two-hundred zeros.
//
// Despite their size, the sum of the digits in each number is only 1.
//
// Considering natural numbers of the form, a^b, where a, b < 100, what is the maximum digital sum ?

//revert multiplication by 'xenon'
void rev_mult(char* s, size_t a)
{
    size_t mult = 0;

    while (*s)
    {
        mult += (*s - '0') * a;
        *s = mult % 10 + '0';
        mult /= 10;
        s++;
    }

    while (mult)
    {
        *s = mult % 10 + '0';
        mult /= 10;
        s++;
    }

    *s = '\0';
}

int main(int argc, char **argv)
{
    size_t max_base = 99;
    size_t max_power = 99;
    size_t max_length = max_power * log10(max_base) + 1;

    size_t max_sum = 0;
    
    char* s = (char*)malloc(sizeof(char) * (max_length + 1));

    for (size_t a = max_base; a != 0; --a)
    {
        if (a % 10 == 0)
            continue;

        sprintf_s(s, 2 * sizeof(char), "1");

        for (size_t b = 1; b <= max_power; ++b)
        {
            rev_mult(s, a);
     
            size_t sum = 0;
            char* p = s;

            while (*p)
                sum += *(p++) - '0';

            if (sum > max_sum)
                max_sum = sum;
        }
    }

    printf("\nResult: %Iu\n", max_sum);

    free(s);

    return 0;
}