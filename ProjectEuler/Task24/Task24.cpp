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
	sort(digits, digits_size);

	size_t size = 0;
	expansion_factorial(serial_number, NULL, &size);
	size_t* fact = (size_t*)malloc(sizeof(size_t) * size);
	expansion_factorial(serial_number, fact, &size);

#ifdef _DEBUG
	printf("\n%Iu = ", serial_number);
	for (int i = size - 1; i >= 0; --i)
		if (fact[i])
			printf("%i!*%Iu + ", i, fact[i]);
	printf("\n");
#endif

	size_t* used_digits = NULL;
	size_t used_size = 0;
	size_t result = 0;
	size_t* current_digit = 0;

	for (int i = digits_size - 1; i >= 0; --i)
	{
		if (i < size)
			current_digit = digits + fact[i];
		else
			current_digit = digits;

		for (size_t j = 0; j < used_size; ++j)
		{
			if (current_digit[0] >= used_digits[j])
				current_digit++;
		}

		result += current_digit[0] * pow(10, i);

		used_size++;
		used_digits = (size_t*)realloc(used_digits, sizeof(size_t) * used_size);
		used_digits[used_size - 1] = current_digit[0];

		sort(used_digits, used_size);
	}

	printf("\nResult[%Iu]: %Iu\n", serial_number + 1, result);

	free(used_digits);

	return 0;
}