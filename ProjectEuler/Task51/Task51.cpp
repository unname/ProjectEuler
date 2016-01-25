#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values : 13, 23, 43, 53, 73, and 83, are all prime.
//
// By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the ten generated numbers,
// yielding the family : 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family, is the smallest prime with this property.
//
// Find the smallest prime which, by replacing part of the number(not necessarily adjacent digits) with the same digit, is part of an eight prime value family.

size_t set_digit(size_t n, size_t d, size_t offset)
{
#ifdef _WIN64
#define MAX_OFFSET 19
#else
#define MAX_OFFSET 9
#endif

    if (offset > MAX_OFFSET)
        return n;

    if (d < 0 || d > 9)
        return n;

    return n / (size_t)pow(10, offset + 1) * (size_t)pow(10, offset + 1) + d * (size_t)pow(10, offset) + n % (size_t)pow(10, offset);
}

int main(int argc, char **argv)
{
#ifdef _WIN64

    size_t count_limit = 8;
    size_t count = 0;
    size_t result = 0;
    
    for (size_t n = 11;; n += 2)
    {
        size_t size = get_digitsize(n);
        size_t bin_size = pow(2, size);

        //mask += 2 -> не смотрим варианты с изменением 0-го разряда числа (т.к тогда max 4 простых числа)
        for (size_t mask = 2; mask < bin_size - 1; mask += 2)
        {
            count = 0;

            //старший разряд не может быть нулём (task: "..six of the nine possible values..")
            for (size_t d = mask < bin_size / 2 ? 0 : 1; d <= 9; ++d)
            {
                size_t m = n;
                
                for (size_t i = 0; i < size; ++i)
                {
                    size_t bit_offset = 1 << i;

                    if (bit_offset > mask)
                        break;

                    if (mask & bit_offset)
                        m = set_digit(m, d, i);
                }

                //проверяем только если числа с нулями/единицами в нужных разрядах (убираем повторы)
                if (d == 0 && m != n || d == 1 && m != n && mask >= bin_size / 2)
                    break;
                
                if (test_prime(m))
                    count++;

                if (count == 1)
                    result = m;

                if (count_limit - count >= 10 - d)
                    break;
            }       

            if (count == count_limit)
                goto end;
        }
    }

end:
    printf("\nResult: %Iu\n", result);
#endif

    return 0;
}
