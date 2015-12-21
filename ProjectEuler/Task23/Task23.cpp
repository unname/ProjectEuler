#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// A  perfect number is a number for which the sum of its proper divisors is exactly equal to the number.
// For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
//
// A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.
//
// As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24.
// By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers.
// However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number
// that cannot be expressed as the sum of two abundant numbers is less than this limit.
//
// Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.

int main(int argc, char **argv)
{
	size_t abundant_limit = 28123;
	size_t size = 0;
	size_t* abundants = NULL;

	for (size_t i = 0; i < abundant_limit; ++i)
	{
		if (test_perfect(i) > 0)
		{
			size++;
			abundants = (size_t*)realloc(abundants, sizeof(size_t) * size);
			abundants[size - 1] = i;
#ifdef _DEBUG
			if (size == 1)
				printf("\nAbundants numbers:\n");
			printf("%Iu ", abundants[size - 1]);
#endif
		}
	}
	
	size_t sum = 0;

	for (size_t i = 1; i <= abundant_limit; ++i)
	{
		bool not_abundant = true;

		for (size_t j = 0; j < size; ++j)
		{
			if (abundants[j] > i)
				break;

			if (test_perfect(i - abundants[j]) > 0)
			{
				not_abundant = false;
				break;
			}
		}

		if (not_abundant)
		{
			sum += i;
		}
	}

	printf("\nSum: %Iu\n", sum);

	free(abundants);

	return 0;
}