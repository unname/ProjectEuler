#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"
#include "windows.h"

// By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
//
//                  3
//                 7 4
//                2 4 6
//               8 5 9 3
//
// That is, 3 + 7 + 4 + 9 = 23.
//
// Find the maximum total from top to bottom of the triangle below :
//
//                     75
//                   95 64
//                  17 47 82
//                 18 35 87 10
//                20 04 82 47 65
//              19 01 23 75 03 34
//             88 02 77 73 07 63 67
//            99 65 04 28 06 16 70 92
//           41 41 26 56 83 40 80 70 33
//         41 48 72 33 47 32 37 16 94 29
//        53 71 44 65 25 43 91 52 97 51 14
//      70 11 33 28 77 73 17 78 39 68 17 57
//     91 71 52 38 17 14 91 43 58 50 27 29 48
//    63 66 04 68 89 53 67 30 73 16 69 87 40 31
//  04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
//
// NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route.
// However, Problem 67, is the same challenge with a triangle containing one - hundred rows; 
// it cannot be solved by brute force, and requires a clever method! ;o)

int main(int argc, char **argv)
{
    size_t triangle[][15] =
    {
        { 75 },
        { 95, 64 },
        { 17, 47, 82 },
        { 18, 35, 87, 10 },
        { 20, 4, 82, 47, 65 },
        { 19, 1, 23, 75, 3, 34 },
        { 88, 2, 77, 73, 7, 63, 67 },
        { 99, 65, 4, 28, 6, 16, 70, 92 },
        { 41, 41, 26, 56, 83, 40, 80, 70, 33 },
        { 41, 48, 72, 33, 47, 32, 37, 16, 94, 29 },
        { 53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14 },
        { 70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57 },
        { 91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48 },
        { 63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31 },
        { 4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23 },
    };

    size_t row_size = sizeof(triangle[0]) / sizeof(size_t);
    size_t column_size = row_size;

    size_t** sum_triangle = (size_t**)malloc(sizeof(size_t*) * column_size);
    for (size_t i = 0; i < column_size; ++i)
        sum_triangle[i] = (size_t*)malloc(sizeof(size_t) * row_size);

    for (int i = column_size - 1; i >= 0; --i)
    {
        for (size_t j = 0; j <= row_size - (column_size - i); ++j)
        {
            if (i != column_size - 1)
                sum_triangle[i][j] = triangle[i][j] + max(sum_triangle[i + 1][j], sum_triangle[i + 1][j + 1]);
            else
                sum_triangle[i][j] = triangle[i][j];
#ifdef _DEBUG
            printf("%Iu ", sum_triangle[i][j]);
            if (j == row_size - (column_size - i))
            {
                printf("\n");
                if (i == 0)
                    printf("\n");
            }
#endif
        }
    }


    size_t result = triangle[0][0];
    size_t row_position = 0;

    for (size_t i = 1; i < column_size; ++i)
    {
        if (sum_triangle[i][row_position + 1] > sum_triangle[i][row_position])
            row_position++;

        result += triangle[i][row_position];

#ifdef _DEBUG
        printf("Collumn(%Iu): %Iu\n", i + 1, triangle[i][row_position]);
#endif 
    }

    printf("\nResult: %Iu\n", result);

    for (size_t i = 0; i < column_size; ++i)
        free(sum_triangle[i]);
    free(sum_triangle);

    return 0;
}