#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
//
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20 ?

int main(int argc, char **argv)
{
    printf("\nAnswer: %Iu\n", 1 * 2 * 2 * 2 * 2 * 3 * 3 * 5 * 7 * 11 * 13 * 17 * 19);

    return 0;
}