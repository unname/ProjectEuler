#include <stdlib.h>
#include <Windows.h>
#include <iostream>

#include "euler_functions.h"


// The 5-digit number, 16807 = 7^5, is also a fifth power. Similarly, the 9-digit number, 134217728 = 8^9, is a ninth power.
//
// How many n-digit positive integers exist which are also an nth power ?

int main(int argc, char **argv)
{
    size_t result = 0;

    for (size_t base = 1; base < 10; ++base)
    {
        char base_s[2];
        char* exp_result = (char*)malloc(sizeof(char) * 2);

        sprintf_s(base_s, 2, "%Iu", base);
        sprintf_s(exp_result, 2, "%Iu", 1);

        for (size_t power = 1; ; ++power)
        {
            size_t size = 0;

            mult_string(exp_result, base_s, NULL, &size);
            exp_result = (char*)realloc(exp_result, sizeof(char) * size);
            mult_string(exp_result, base_s, exp_result, &size);

            if (strlen(exp_result) == power)
                result++;
            else
                break;
        }

        free(exp_result);
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}