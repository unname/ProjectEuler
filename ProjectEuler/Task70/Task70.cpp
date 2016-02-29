#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of positive numbers less than or equal to n which are relatively prime to n.
//
// For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
// The number 1 is considered to be relatively prime to every positive number, so φ(1) = 1.
//
// Interestingly, φ(87109) = 79180, and it can be seen that 87109 is a permutation of 79180.
//
// Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of n and the ratio n / φ(n) produces a minimum.

int main(int argc, char **argv)
{
    // 1) Ratio n / φ(n) produces a minimum:
    //          this condition can be obtain if : phi(n)->n       and   n->infinity
    //          for other task it means         : phi(n)->(n - 1) and   n->10^7
    //          so if we get max prime number < 10^7 it will be the answer

    // 2) φ(n) is a permutation of n
    //          this condition reject answers when n is prime (n and n-1 can't be permutation)
    //          so we try to use the property of phi function and will search product of two primes that provide max value
    //          (it can be that product of 3 or more primes will be higher then of 2, but product of phi, what is most important, were less)
    //          other new condition for n is: n = n1 * n2, n1 * n2 -> 10^7 and phi(n1) * phi(n2)-> n - 1.
    //
    //          for example: etalon value = phi(9997619) = phi(3137 * 3187) = 3136 * 3186 = 9991296;  Ratio = 1,000632850833365

    size_t upper_limit = 10000000;

    size_t n1_max = sqrt(upper_limit);

    while (!test_prime(n1_max))
    {
        n1_max--;
    }

    size_t result = 0;
    double lowest_ration = 2;
    size_t n2_low = 0;

    for (size_t n1 = n1_max; n1 > 1; n1 -= 2)
    {
        if (!test_prime(n1))
            continue;

        for (size_t n2 = max(n1, n2_low + 2); n1 * n2 < upper_limit; n2 += 2)
        {
            if (!test_prime(n2))
                continue;

            if (test_permut(n1 * n2, (n1 - 1) * (n2 - 1)))
            {
                double ratio = ((double)n1 * (double)n2) / ((double)(n1 - 1) * (double)(n2 - 1));

                if (ratio < lowest_ration)
                {
                    result = n1 * n2;
                    lowest_ration = ratio;
                }

                n2_low = n2;
                break;
            }
        }

        double max_ratio = (double)(n1 * (upper_limit / n1)) / (double)((n1 - 1) * (upper_limit / n1 - 1));

        if (max_ratio > lowest_ration)
            break;
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}