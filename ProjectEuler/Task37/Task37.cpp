#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The number 3797 has an interesting property.Being prime itself, it is possible to continuously remove digits from left to right,
// and remain prime at each stage : 3797, 797, 97, and 7. Similarly we can work from right to left : 3797, 379, 37, and 3.
//
// Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
//
// NOTE : 2, 3, 5, and 7 are not considered to be truncatable prime

int main(int argc, char **argv)
{
#ifdef _WIN64
    size_t num_limit = 11;
    size_t num_count = 0;

    size_t result = 0;
    size_t n = 11;

    while (num_count != num_limit)
    {
        //Отсеиваем если есть определённые цифры 
        size_t n1 = n;

        while (n1)
        {
            if ((n1 > 9) && (n1 % 10 % 2 == 0 || n1 % 10 == 5))
                goto end;

            if ((n1 < 10) && (n1 == 1 || n1 == 4 || n1 == 6 || n1 == 8 || n1 == 9))
                goto end;

            n1 /= 10;
        }
        
        //Отсеиваем если число не простое
        if (!test_prime(n))
            goto end;

        //Отсеиваем right to left
        n1 = n;

        while (n1)
        {
            n1 /= 10;

            if (!test_prime(n1) && n1)
                 goto end;
        }

        //Отсеиваем left to right
        n1 = n;

        while (n1)
        {
            n1 %= (size_t)pow(10, get_digitsize(n1) - 1);

            if (!test_prime(n1) && n1)
                goto end;
        }

        num_count++;
        result += n;

#ifdef _DEBUG
        printf("%Iu) %Iu\n", num_count, n);
#endif
        
    end:
        n += 2;
    }

    printf("\nResult: %Iu\n", result);
#endif 

    return 0;
}
