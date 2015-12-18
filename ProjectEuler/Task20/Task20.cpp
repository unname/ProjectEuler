#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// n! means n ×(n − 1) × ... × 3 × 2 × 1
//
// For example, 10!= 10 × 9 × ... × 3 × 2 × 1 = 3628800,
// and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
// 
// Find the sum of the digits in the number 100!

int main(int argc, char **argv)
{
	size_t size = 0;

	factorial_string(100, NULL, &size);
	char* fact = (char*)malloc(sizeof(char) * size);
	factorial_string(100, fact, &size);

	printf("\nFactorial: %s\n", fact);

	size_t sum = 0;
	for (size_t i = 0; i < size - 1; ++i)
		sum += fact[i] - '0';

	printf("\nDigit sum: %Iu\n", sum);

	free(fact);

	return 0;
}