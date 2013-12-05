#include <stdlib.h>
#include <iostream>

void func1(unsigned int k1, unsigned int k2, unsigned int *pOut, unsigned int *ulOut, unsigned int x, ... )
{
	unsigned int *pIn;
	*ulOut = 0;

	for(unsigned int i = k1; i<=k2; i++)
	{
		//Начинаем с первого делителя
		pIn = &x;

		while (*pIn)
		{
			if(i % *pIn)
			{
				pIn++;
			}
			else
			{
				//Можно вернуть просто длину, если указатель на массив не задан
				if(pOut)
				{
					*pOut = i;
					pOut++;
					*ulOut += 1;
				}
				else
				{
					*ulOut += 1;
				}

				break;
			}
		}

	}
	
}


int main(int argc, char **argv)
{
	unsigned int *p;
	unsigned int len;

	func1(1, 1000, NULL, &len, 3, 5); 

	p = (unsigned int*) malloc (sizeof(unsigned int) * len);

	func1(1, 1000, p, &len, 3, 5); 

	//Считаем сумму всех найденных чисел
	unsigned int sum = 0;

	for(int i=0; i<len; i++)
	{
		sum += p[i];		
	}
	
	printf("Sum = %u", sum);

	free(p);

	return 0;
}