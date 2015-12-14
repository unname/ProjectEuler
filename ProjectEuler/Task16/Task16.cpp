#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
// 
// What is the sum of the digits of the number 2^1000 ?

int main(int argc, char **argv)
{
    size_t size = 0;
 
    pow_string("2", 1000, NULL, &size);

#ifdef _DEBUG
    printf("\nExp_length: %Iu\n", size);
#endif

    char* result = (char*)malloc(sizeof(char) * size);
    pow_string("2", 1000, result, &size);

#ifdef _DEBUG
    printf("\nExp: %s\n", result);
#endif

    size_t sum = 0;

    for (size_t i = 0; i < size - 1; ++i)
    {
        sum += result[i] - '0';
    }

    printf("\nSum: %Iu\n", sum);

    free(result);

    return 0;
}