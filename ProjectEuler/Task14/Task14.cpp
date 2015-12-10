#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The following iterative sequence is defined for the set of positive integers :
//
//      n → n / 2 (n is even)
//      n → 3n + 1 (n is odd)
//
// Using the rule above and starting with 13, we generate the following sequence :
//
//      13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
//
// It can be seen that this sequence(starting at 13 and finishing at 1) contains 10 terms.
// Although it has not been proved yet(Collatz Problem), it is thought that all starting numbers finish at 1.
//
// Which starting number, under one million, produces the longest chain ?
//
// NOTE : Once the chain starts the terms are allowed to go above one million.

int main(int argc, char **argv)
{
    size_t* p;
    size_t len = 0;
    size_t number = 1;
    size_t max_len = 0;
    size_t max_number = 0;

    while (number < 1000000)
    {
        get_сollatz(number, NULL, &len);
        
        if (max_len < len)
        {
            max_len = len;
            max_number = number;
        }

        number++;
    }

    printf("\nMax number(len:%Iu) = %Iu\n", max_len, max_number);

#ifdef _DEBUG
    p = (size_t*)malloc(sizeof(size_t) * max_len);
    get_сollatz(max_number, p, &len);

    for (size_t i = 0; i < len; ++i)
    {
        if (i % 10 == 0)
        {
            printf("\n");
        }

        if (p[i] != 1)
            printf("%Iu->", p[i]);
        else
            printf("%Iu\n", p[i]);
    }

    free(p);
#endif

    return 0;
}