#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#include "euler_functions.h"


// By counting carefully it can be seen that a rectangular grid measuring 3 by 2 contains eighteen rectangles :
//
//                6               4               2
//          | X | _ | _ |   | X | X | _ |   | X | X | X |
//          | _ | _ | _ |   | _ | _ | _ |   | _ | _ | _ |
//           
//                3               2               1
//          | X | _ | _ |   | X | X | _ |   | X | X | X |
//          | X | _ | _ |   | X | X | _ |   | X | X | X |
//
// Although there exists no rectangular grid that contains exactly two million rectangles, find the area of the grid with the nearest solution.

size_t abs(size_t a, size_t b)
{
    return max(a, b) - min(a, b);
}

size_t count_rect(size_t x, size_t y, size_t max_value)
{
    if (!x || !y)
        return 0;

    size_t count = 0;

    for (size_t i = 1; i <= x; ++i)
        for (size_t j = 1; j <= y; ++j)
        {
            count += (x - i + 1) * j;

            if (count > max_value)
                return count;
        }

    return count;
}

int main(int argc, char **argv)
{
    size_t limit    = 2000000;

    size_t count    = 0;
    size_t result   = 0;

    size_t nearest_x = 0;
    size_t nearest_y = 0;

    for (size_t x = 1;; ++x)
    {
        printf("\rx: %Iu", x);

        for (size_t y = 1; y <= x; ++y)
        {
            count = count_rect(x, y, limit + abs(limit, result));

            if (abs(limit, count) < abs(limit, result))
            {
                nearest_x = x;
                nearest_y = y;

                result = count;
            }

            if (y == 1 && count > limit)
                goto end;
        }
    }

end:
    printf("\n\nResult: %Iu\n", nearest_x * nearest_y);

    return 0;
}