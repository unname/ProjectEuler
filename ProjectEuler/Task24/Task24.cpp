#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation of the digits 1, 2, 3 and 4.
// If all of the permutations are listed numerically or alphabetically, we call it lexicographic order.The lexicographic permutations of 0, 1 and 2 are:
//
// 012   021   102   120   201   210
//
// What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9 ?

int main(int argc, char **argv)
{
    size_t serial_number = 1000000 - 1; //Так как 0123456789 - это serial_number = 0

	size_t digits[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	size_t digits_size = sizeof(digits) / sizeof(size_t);
	
    printf("\nResult[%Iu]: %Iu\n", serial_number + 1, get_lex_permut(digits, digits_size, serial_number));

	return 0;
}