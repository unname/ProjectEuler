﻿#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Euler discovered the remarkable quadratic formula :
//
//               n^2 + n + 41
//
// It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39.
// However, when n = 40, 40^2 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41,
// and certainly when n = 41, 41^2 + 41 + 41 is clearly divisible by 41.
//
// The incredible formula  n^2 − 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79.
// The product of the coefficients, −79 and 1601, is −126479.
//
// Considering quadratics of the form :
//
//     n^2 + an + b, where | a | < 1000 and | b | < 1000
//
//     where | n | is the modulus / absolute value of n
//     e.g. | 11 | = 11 and | −4 | = 4
//
// Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes 
// for consecutive values of n, starting with n = 0.

int main(int argc, char **argv)
{
	size_t max_size = 0;
	int result = 0;;

	for (int a = -999; a < 1000; ++a)
	{
		for (int b = 2; b < 1000; ++b)
		{
			//при таких условиях не пройдёт n = 1;
			if (a < 0 && abs(a) >= b)
			{
				b = abs(a);
				continue;
			}

			//При таких условия не пройдёт n = 0;
			if (!test_prime(b))
			{
				continue;
			}

			size_t n = 0;

			while (test_prime(n * n + a * n + b))
			{
				n++;
			}

			if (max_size < n)
			{
				max_size = n;
				result = a * b;
			}

#ifdef _DEBUG
			if (n > 10)
				printf("n^2 %in + %i = (%Iu)\n", a, b, n);
#endif
		}
	}

	printf("\nResult: %i\n", result);

	return 0;
}