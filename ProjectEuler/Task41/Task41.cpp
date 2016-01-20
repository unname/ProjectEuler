#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once.
// For example, 2143 is a 4 - digit pandigital and is also prime.
//
// What is the largest n-digit pandigital prime that exists ?

int main(int argc, char **argv)
{
#ifdef _WIN64
    size_t digits[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
 
    for (size_t size = sizeof(digits) / sizeof(digits[0]); size > 0; --size)
    {
        size_t serial_number = factorial(size);

        do
        {
            serial_number--;

            size_t n = get_lex_permut(digits, size, serial_number);

            if (test_prime(n))
            {
                printf("\nResult: %Iu\n", n);
                return 0;
            }
        } while (serial_number != 0);
    }
#endif

    return 0;
}
