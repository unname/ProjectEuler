#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
//
// Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000

int main(int argc, char **argv)
{   
#ifdef _WIN64
    size_t precision = 10;
    size_t result = 0;

    for (size_t n = 1; n <= 1000; ++n)
    {
        size_t n_result = n;

        for (size_t i = 1; i < n; ++i)
        {
            n_result = n_result * n % (size_t)pow(10, precision);
        }

        result += n_result;
        result %= (size_t)pow(10, precision);
    }

    printf("\nResult: %Iu\n", result);
#endif

    return 0;
}
