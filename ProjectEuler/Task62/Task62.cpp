#include <stdlib.h>
#include <Windows.h>
#include <iostream>

#include "euler_functions.h"


// The cube, 41063625 (345^3), can be permuted to produce two other cubes : 56623104 (384^3) and 66430125 (405^3).
// In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.
//
// Find the smallest cube for which exactly five permutations of its digits are cube.

int main(int argc, char **argv)
{
#ifdef _WIN64

    const size_t permutation_count_expect = 5;
    const size_t start_n = 5;
    size_t cube = 125;

    size_t result = 0;

    size_t permutations_size = 1;
    size_t** permutations = (size_t**)malloc(sizeof(size_t*) * permutations_size);
    permutations[permutations_size - 1] = (size_t*)malloc(sizeof(size_t) * 2);

    permutations[permutations_size - 1][0] = pow(start_n, 3);
    permutations[permutations_size - 1][1] = 0;

    size_t cube_size = get_digitsize(permutations[permutations_size - 1][0]);
    size_t previous_cube_size = cube_size;

    printf("\n");

    for (size_t number = start_n + 1; ; ++number)
    {
        cube += 3 * number * (number - 1) + 1;
        cube_size = get_digitsize(cube);

#ifdef _DEBUG
        printf("\rNumber(%Iu): %Iu", cube_size, number);
#endif

        for (size_t i = 0; i < permutations_size; ++i)
        {
            if (cube_size > previous_cube_size)
            {
                for (size_t i = 0; i < permutations_size; ++i)
                    free(permutations[i]);
                free(permutations);

                permutations_size = 1;
                permutations = (size_t**)malloc(sizeof(size_t*) * permutations_size);
                permutations[permutations_size - 1] = (size_t*)malloc(sizeof(size_t) * 2);

                permutations[permutations_size - 1][0] = cube;
                permutations[permutations_size - 1][1] = 0;

                previous_cube_size = cube_size;

                break;
            }

            if (test_permut(permutations[i][0], cube))
            {
                permutations[i][1]++;

                if (permutations[i][1] + 1 == permutation_count_expect)
                {
                    result = permutations[i][0];
                    goto end;
                }

                break;
            }
            
            if (i + 1 == permutations_size)
            {
                permutations_size++;
                permutations = (size_t**)realloc(permutations, sizeof(size_t*) * permutations_size);
                permutations[permutations_size - 1] = (size_t*)malloc(sizeof(size_t) * 2);

                permutations[permutations_size - 1][0] = cube;
                permutations[permutations_size - 1][1] = 0;

                break;
            }
        }
    }
end:

    printf("\nResult: %Iu\n", result);

    for (size_t i = 0; i < permutations_size; ++i)
        free(permutations[i]);
    free(permutations);

#endif

    return 0;
}