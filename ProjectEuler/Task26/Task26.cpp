#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


//A  unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
//
//    1/2	= 	0.5
//    1/3	= 	0.(3)
//    1/4	= 	0.25
//    1/5	= 	0.2
//    1/6	= 	0.1(6)
//    1/7	= 	0.(142857)
//    1/8	= 	0.125
//    1/9	= 	0.(1)
//    1/10	= 	0.1 
//
// Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.
//
// Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.

int main(int argc, char **argv)
{
	size_t denominator_limit = 999;
	size_t result = 1;
	size_t max_size = 0;

	for (size_t i = 2; i <= denominator_limit; ++i)
	{
		size_t numerator = 1;

		size_t size = 0;
		size_t* used_numerator = NULL;
		
		bool deleting = true;

#ifdef _DEBUG
		printf("\n%Iu = 0.", i);
#endif

		while (numerator)
		{
			if (numerator < i)
			{
				numerator *= 10;
			}

			if (numerator >= 10)
			{
				for (size_t j = 0; j < size; ++j)
				{
					if (numerator == used_numerator[j])
					{
						if (max_size < size - j)
						{
							max_size = size - j;
							result = i;
						}

#ifdef _DEBUG
						printf("~");
#endif
						deleting = false;
						break;
					}
				}

				if (!deleting)
					break;

				size++;
				used_numerator = (size_t*)realloc(used_numerator, sizeof(size_t) * size);
				used_numerator[size - 1] = numerator;

#ifdef _DEBUG
				printf("%Iu", numerator/i);
#endif

				if (numerator >= i)
					numerator %= i;
			}
		}

		free(used_numerator);
	}

	printf("\nDenominator(%Iu): %Iu\n", max_size, result);

	return 0;
}