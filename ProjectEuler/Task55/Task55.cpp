#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
//
// Not all numbers produce palindromes so quickly.
//
// For example,
//
//      349 + 943   = 1292,
//      1292 + 2921 = 4213
//      4213 + 3124 = 7337
//
// That is, 349 took three iterations to arrive at a palindrome.
//
// Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome.
// A number that never forms a palindrome through the reverse and add process is called a Lychrel number.
// Due to the theoretical nature of these numbers, and for the purpose of this problem, we shall assume that a number is Lychrel until proven otherwise.
// In addition you are given that for every number below ten-thousand, it will either:
//  (i)  become a palindrome in less than fifty iterations, or,
//  (ii) no one, with all the computing power that exists, has managed so far to map it to a palindrome.
//
// In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome : 4668731596684224866951378664 (53 iterations, 28 - digits).
//
// Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.
//
// How many Lychrel numbers are there below ten-thousand ?
//
// NOTE : Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.

int main(int argc, char **argv)
{
    size_t result = 0;
    size_t number_limit = 10000;
    size_t count_limit = 50;

    for (size_t n = 0; n < number_limit; ++n)
    {
        size_t length = get_digitsize(n) + 1;
        char* num = (char*)malloc(sizeof(char) * (length));
        sprintf_s(num, length, "%Iu", n);

        for (size_t i = 1; i < count_limit; ++i)
        {
            char* rev_num = (char*)malloc(sizeof(char) * length);
            for (size_t i = 0; i < length - 1; ++i)
                rev_num[i] = num[length - 2 - i];
            rev_num[length - 1] = '\0';

            sum_string(num, rev_num, NULL, &length);
            num = (char*)realloc(num, length * sizeof(char));
            sum_string(num, rev_num, num, &length);

            if (test_palindrome(num, length - 1))
                break;

            if (i == count_limit - 1)
            {
#ifdef _DEBUG
                printf("%Iu\n", n);
#endif
                result++;
            }

            free(rev_num);
        }

        free(num);
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}