#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"

int main(int argc, char **argv)
{
    size_t *p;
    size_t len;

	func1(1, 999, NULL, &len, 3, 5); 
    p = (size_t*)malloc(sizeof(size_t) * len);
	func1(1, 999, p, &len, 3, 5); 

	//—читаем сумму всех найденных чисел
	size_t sum = 0;
    for (size_t i = 0; i<len; i++)
	{
		sum += p[i];		
	}
	
	printf("Sum = %u", sum);

	free(p);

	return 0;
}