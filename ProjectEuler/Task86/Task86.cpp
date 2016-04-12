#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include "euler_functions.h"


// A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3, and a fly, F, sits in the opposite corner.
// By travelling on the surfaces of the room the shortest "straight line" distance from S to F is 10 and the path is shown on the diagram.
//
// However, there are up to three "shortest" path candidates for any given cuboid and the shortest route doesn't always have integer length.
//
// It can be shown that there are exactly 2060 distinct cuboids, ignoring rotations, with integer dimensions, up to a maximum size of M by M by M,
// for which the shortest route has integer length when M = 100. This is the least value of M for which the number of solutions first exceeds two thousand;
// the number of solutions when M = 99 is 1975.
//
// Find the least value of M such that the number of solutions first exceeds one million.

// TODO: The slowest part of task is M counting. It can be accelerating by binary searching, if you need.

int main(int argc, char **argv)
{
    size_t upper_bound = 1000000;

    for (size_t M = 1;; ++M)
    {
        size_t solution_count = 0;

        // Triplets generation
        //
        // a = k * (m^2 - n^2)
        // b = k * 2mn 
        // c = k * (m^2 + n^2)

        for (size_t m = 2;; ++m)
        {
            for (size_t n = m % 2 ? 2 : 1; n < m; n += 2)
            {
                if (gcd(m, n) != 1)
                {
                    continue;
                }

                size_t sqr_m = (size_t)pow(m, 2);

                if (m * 2 > M && sqr_m - (size_t)pow(m - 1, 2) > M)
                    goto next_M;

                size_t sqr_n = (size_t)pow(n, 2);

                size_t triplet[3];

                triplet[0] = sqr_m - sqr_n;
                triplet[1] = 2 * m * n;
                triplet[2] = sqr_m + sqr_n;

                sort(triplet, 3);

                for (size_t k = 1;; ++k)
                {
                    size_t sides[3] = { triplet[0] * k, triplet[1] * k, triplet[2] * k };

                    if (sides[0] > M || sides[0] <= M && sides[1] > 2 * M)
                        break;

                    if (sides[1] <= M)
                        solution_count += sides[0] / 2;

                    if (sides[1] - sides[0] <= sides[1] / 2)
                        solution_count += sides[1] / 2 - (sides[1] - sides[0] - 1);

                }
            }
        }
    next_M:

        if (solution_count > upper_bound)
        {
            printf("\nResult(%Iu): %Iu\n", solution_count, M);
            break;
        }
    }

    return 0;
}