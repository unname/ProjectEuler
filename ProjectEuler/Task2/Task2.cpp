#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Each new term in the Fibonacci sequence is generated by adding the previous two terms.By starting with 1 and 2, the first 10 terms will be :
//
// 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
//
// By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even - valued terms.

int main(int argc, char **argv)
{
    size_t *p;
    size_t len;

    get_fibonacci(1, 1, 4000000, NULL, &len, true);
    p = (size_t*)malloc(sizeof(size_t) * len);
    get_fibonacci(1, 1, 4000000, p, &len, true);

    //������� ����� ���� ��������� ������ �����
    size_t sum = 0;
    for (size_t i = 0; i<len; i++)
    {
        if (p[i]%2 == 0)
            sum += p[i];
    }

    printf("\nSum = %Iu\n", sum);

    free(p);

    return 0;
}