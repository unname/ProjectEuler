#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// We shall say that an n - digit number is pandigital if it makes use of all the digits 1 to n exactly once;
// for example, the 5 - digit number, 15234, is 1 through 5 pandigital.
//
// The product 7254 is unusual, as the identity, 39 * 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
//
// Find the sum of all products whose multiplicand / multiplier / product identity can be written as a 1 through 9 pandigital.
//
// HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.

bool test_pandigital_product(size_t a, size_t b)
{
    size_t c = 0;
    c = a * b;

    if (get_digitsize(a) + get_digitsize(b) + get_digitsize(c) != 9)
        return false;

    size_t result = 0;

    while (a || b || c)
    {
        if (a % 10)
            result |= 1 << (a % 10 - 1);
        if (b % 10)
            result |= 1 << (b % 10 - 1);
        if (c % 10)
            result |= 1 << (c % 10 - 1);

        a /= 10;
        b /= 10;
        c /= 10;
    }

    if (result == 0x1FF)
        return true;
    else
        return false;
}

int main(int argc, char **argv)
{
    size_t* products = NULL;
    size_t size = 0;

    for (size_t a = 1; a < 10; ++a)
    {
        for (size_t b = 1000; b < 10000; ++b)
        {
            if (test_pandigital_product(a, b))
            {
                size++;
                products = (size_t*)realloc(products, sizeof(size_t) * size);

                products[size - 1] = a * b;
#ifdef _DEBUG
                printf("%Iu * %Iu = %Iu\n", a, b, products[size - 1]);
#endif
            }
        }
    }

    for (size_t a = 10; a < 100; ++a)
    {
        for (size_t b = 100; b < 1000; ++b)
        {
            if (test_pandigital_product(a, b))
            {
                size++;
                products = (size_t*)realloc(products, sizeof(size_t) * size);

                products[size - 1] = a * b;
#ifdef _DEBUG
                printf("%Iu * %Iu = %Iu\n", a, b, products[size - 1]);
#endif
            }
        }
    }

    size_t result = 0;

    for (size_t i = 0; i < size; ++i)
    {
        bool single = true;
        for (size_t j = 0; j < i; ++j)
        {
            if (products[i] == products[j])
                single = false;
        }

        if (single)
            result += products[i];
    }

    printf("\nResult: %Iu\n", result);

    free(products);

    return 0;
}
