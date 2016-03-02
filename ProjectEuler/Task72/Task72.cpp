#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"

#include <vector>

using namespace std;

// Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d) = 1, it is called a reduced proper fraction.
//
// If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get :
//
//  1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
//
// It can be seen that there are 21 elements in this set.
//
// How many elements would be contained in the set of reduced proper fractions for d ≤ 1,000,000 ?

int main(int argc, char **argv)
{
#ifdef _WIN64
    //Farey sequence length: |F(n)| = |F(n-1)| + phi(n); 

    size_t d = 1000000;

    size_t result = 0;

    for (size_t i = 2; i <= d; ++i)
    {
        result += phi(i);
    }

    printf("\nResult: %Iu\n", result);

#endif

    return 0;
}