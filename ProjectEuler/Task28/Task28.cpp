#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows :
//
//          21 22 23 24 25
//          20  7  8  9 10
//          19  6  1  2 11
//          18  5  4  3 12
//          17 16 15 14 13
//
// It can be verified that the sum of the numbers on the diagonals is 101.
//
// What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way ?

int main(int argc, char **argv)
{
    size_t spiral_size = 1001;
    size_t sum = 1;
    size_t next_number = 1;

    for (size_t i = 1; i <= (spiral_size - 1) / 2; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            next_number += i * 2;
            sum += next_number;
        }
    }

    printf("\nResult: %Iu\n", sum);

	return 0;
}