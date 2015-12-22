#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The Fibonacci sequence is defined by the recurrence relation :
//
// Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
//
// Hence the first 12 terms will be :
//
// F1 = 1
// F2 = 1
// F3 = 2
// F4 = 3
// F5 = 5
// F6 = 8
// F7 = 13
// F8 = 21
// F9 = 34
// F10 = 55
// F11 = 89
// F12 = 144
//
// The 12th term, F12, is the first term to contain three digits.
//
// What is the index of the first term in the Fibonacci sequence to contain 1000 digits ?

int main(int argc, char **argv)
{
	size_t limit_size = 1000;

	size_t size = 2;
	char* n1 = (char*)malloc(sizeof(char) * size);
	char* n2 = (char*)malloc(sizeof(char) * size);
	char* n;
	n1[0] = '1';
	n2[0] = '1';
	n1[1] = '\0';
	n2[1] = '\0';

	size_t index = 2;

	while (size - 1 != limit_size)
	{
		sum_string(n1, n2, NULL, &size);
		n1 = (char*)realloc(n1, sizeof(char) * size);
		n2 = (char*)realloc(n2, sizeof(char) * size);
		sum_string(n1, n2, n1, &size);
		
		n = n1;
		n1 = n2;
		n2 = n;

		index++;

#ifdef _DEBUG
		printf("F(%Iu): %s\n", index, n2);
#endif
	}

	printf("\nResult: %Iu\n", index);

	// Решение сообщеста ProjectEuler
	//
	// The nth Fibonacci number is[phi**n / sqrt(5)],
	// where the brackets denote "nearest integer".
	//	
	// So we need phi**n / sqrt(5) > 10 * *999 
	//
	// n * log(phi) - log(5) / 2 > 999 * log(10)
	// n * log(phi) > 999 * log(10) + log(5) / 2
	// n > (999 * log(10) + log(5) / 2) / log(phi)

	double phi = (1 + sqrt(5)) / 2;
	printf("\nResult(by community): %.0f\n", round((999 * log(10) + log(5) / 2) / log(phi)));

	free(n1);
	free(n2);

	return 0;
}