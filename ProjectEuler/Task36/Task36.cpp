#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// The decimal number, 585 = 1001001001~2 (binary), is palindromic in both bases.
//
// Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
//
// (Please note that the palindromic number, in either base, may not include leading zeros.)

// This sample can be update by 'runtime' by this alg: http://habrahabr.ru/post/272659/

int main(int argc, char **argv)
{
    size_t result = 0;
    size_t num = 0;

    size_t max_number = 1000000 - 1;
    size_t max_size = get_digitsize(max_number);
    size_t max_generator = max_number / pow(10, max_size / 2);
    size_t max_gen_size = get_digitsize(max_generator);
 
    // Генерируем ~10 полиндромы

    for (size_t size = 1; size <= max_gen_size; ++size)
    {
        for (size_t gen_type = 0; gen_type < 2; ++gen_type)
        {
            for (size_t j = pow(10, size - 1); j < min(max_generator, pow(10, size)); ++j)
            {
                // Пропускам чётные числа так как они не могут быть полиндромами в ~2
                if ((j / (size_t)pow(10, size - 1)) % 2 == 0)
                    j += pow(10, size - 1);

                size_t n = 0;

                //генерируем с нечётной длиной знаков
                if (gen_type == 0)
                {
                    n = j * pow(10, size - 1);

                    for (size_t k = 1; k <= size - 1; ++k)
                    {
                        n += j % (size_t)pow(10, size - k + 1) / (size_t)pow(10, size - k) * pow(10, k - 1);
                    }
                }

                //генерируем с чётной длиной знаков
                if ((gen_type == 1) && (max_size <= max_gen_size * 2))
                {
                    n = j * pow(10, size);

                    for (size_t k = 1; k <= size; ++k)
                    {
                        n += j % (size_t)pow(10, k) / (size_t)pow(10, k - 1) * pow(10, size - k);
                    }
                }

                //Проверяем полиндромность в ~2
                if (test_palindrome(n, 2))
                {
                    result += n;
                    num++;
#ifdef _DEBUG
                    printf("%Iu) %Iu\n", num, n);
#endif
                }
            }
        }
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}
