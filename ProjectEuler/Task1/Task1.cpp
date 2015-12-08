#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
//
// Find the sum of all the multiples of 3 or 5 below 1000.

int main(int argc, char **argv)
{
    size_t *p;
    size_t len;

    get_dividend_by_divisor(1, 999, NULL, &len, 3, 5);
    p = (size_t*)malloc(sizeof(size_t) * len);
    get_dividend_by_divisor(1, 999, p, &len, 3, 5);

	//—читаем сумму всех найденных чисел
	size_t sum = 0;
    for (size_t i = 0; i<len; i++)
	{
		sum += p[i];		
	}
	
	printf("\nSum = %Iu\n", sum);

	free(p);

	return 0;
}