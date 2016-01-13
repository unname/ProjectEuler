#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Take the number 192 and multiply it by each of 1, 2, and 3:
//
//      192 × 1 = 192
//      192 × 2 = 384
//      192 × 3 = 576
//
// By concatenating each product we get the 1 to 9 pandigital, 192384576. We will call 192384576 the concatenated product of 192 and(1, 2, 3)
//
// The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the pandigital, 918273645, which is the concatenated product of 9 and(1, 2, 3, 4, 5).
//
// What is the largest 1 to 9 pandigital 9 - digit number that can be formed as the concatenated product of an integer with(1, 2, ..., n) where n > 1 ?

// Можно добавить проверку чтобы смотрел только числа начинающиеся с '9'
// Но для красоты найдём все

int main(int argc, char **argv)
{
    char result[10] = "123456789";

    for (size_t i_size = 0; i_size < 4; ++i_size)
    {
        size_t low_bounds[] = {5, 25, 100, 5000};
        size_t up_bounds[]  = {9, 33, 333 ,9999};

        for (size_t i = low_bounds[i_size]; i <= up_bounds[i_size]; ++i)
        {
            char s_num[10];
            char* p = &s_num[0];

            for (size_t n = 1; n <= 5 - i_size; ++n)
            {
                sprintf_s(p, get_digitsize(n * i) + 1, "%Iu", n * i);
                p += get_digitsize(n * i);
            }

            if (test_pandigital(atoi(s_num)))
            {
#ifdef _DEBUG
                printf("i = %Iu: %s\n", i, s_num);
#endif
                if (strcmp(s_num, result) > 0)
                    strcpy_s(result, 10, s_num);
            }
        }
    }

    printf("\nResult: %s\n", result);

    return 0;
}
