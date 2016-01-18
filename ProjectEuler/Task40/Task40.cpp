#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


//An irrational decimal fraction is created by concatenating the positive integers :
//
//      0.123456789101112131415161718192021...
//
//It can be seen that the 12th digit of the fractional part is 1.
//
//If 'dn' represents the nth digit of the fractional part, find the value of the following expression.
//
//d1 × d10 × d100 × d1000 × d10000 × d100000 × d1000000

unsigned char get_digit(size_t n)
{
    if (n < 10)
        return n;
    else
        n -= 9;
    
    size_t k = 90;
    size_t size = 2;

    while (n > k * size)
    {
        n -= k * (size);
        k = k * 10;
        size = get_digitsize(k);
    }

    switch (n % size)
    {
    case 0:
            return (n / size - 1) % 10;
        break;
    case 1:
        return n / (size * (size_t)pow(10, size - 1)) + 1;
        break;
    default:
        return (n / (size * (size_t)pow(10, n % size - 1))) % 10;
        break;
    }
}

int main(int argc, char **argv)
{
    printf("\nResult: %u x %u x %u x %u x %u x %u x %u = ", get_digit(1), get_digit(10), get_digit(100), get_digit(1000), get_digit(10000), get_digit(100000), get_digit(1000000));
    printf("%Iu\n", get_digit(1) * get_digit(10) * get_digit(100) * get_digit(1000) * get_digit(10000) * get_digit(100000) * get_digit(1000000));

    return 0;
}
