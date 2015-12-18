#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Let d(n) be defined as the sum of proper divisors of n(numbers less than n which divide evenly into n).
// If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
//
// For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
//
// Evaluate the sum of all the amicable numbers under 10000.

int main(int argc, char **argv)
{
	size_t limit = 10000;
	size_t sum = 0;

	for (size_t a = 1; a < limit; ++a)
	{
		size_t size = 0;
		size_t b = 0;
		size_t d = 0;

		get_divisor_by_dividend(a, NULL, &size);
		size_t* divisors = (size_t*)malloc(sizeof(size_t) * size);
		get_divisor_by_dividend(a, divisors, &size);

		
		for (size_t i = 0; i < size; ++i)
			b += divisors[i];
		if (a != 1)
			b -= a;

		else
			b = 1;

		free(divisors);

		if (a == b)
			continue;

		get_divisor_by_dividend(b, NULL, &size);
		divisors = (size_t*)malloc(sizeof(size_t) * size);
		get_divisor_by_dividend(b, divisors, &size);


		for (size_t i = 0; i < size; ++i)
			d += divisors[i];
		if (b != 1)
			d -= b;

		if (a == d)
		{
			sum += a + b;
#ifdef _DEBUG
			printf("a: %Iu b: %Iu\n", a, b);
#endif
		}

		free(divisors);
	}

	printf("\nSum: %Iu\n", sum / 2);

	return 0;
}