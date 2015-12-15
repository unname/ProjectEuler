#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// If the numbers 1 to 5 are written out in words : one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
//
// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used ?
//
// NOTE : Do not count spaces or hyphens. For example, 342 (three hundred and forty - two) contains 23 letters and 115 (one hundred and fifteen) contains 20 letters.
// The use of "and" when writing out numbers is in compliance with British usage.

int main(int argc, char **argv)
{
    char* units[] =
    {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
    };

    char* first_ten[] =
    {
        "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
    };

    char* tens[] =
    {
        "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety",
    };

    char* hundreds[] =
    {
        "hundred", "thousand",
    };

    size_t limit = 1000;
    size_t result = 0;

    for (size_t i = 1; i <= limit; ++i)
    {
        //1-9
        if (i % 100 < 10)
            result += strlen(units[i % 10]);
        else
            //11-19
            if (i % 100 > 10 && i % 100 < 20)
                result += strlen(first_ten[i % 10 - 1]);
            else
                //10,20-99
                result += strlen(tens[i % 100 / 10 - 1]) + strlen(units[i % 10]);
        //100,200 .. 900
        if (i >= 100)
        {
            if (i % 1000 / 100)
                result += strlen(units[i % 1000 / 100]) + strlen(hundreds[0]);

            if (i % 100)
                result += strlen("and");
        }
        
        //1000,2000 .. 9000
        if (i >= 1000)
        {
            if (i % 10000 / 1000)
                result += strlen(units[i % 10000 / 1000]) + strlen(hundreds[1]);
        }
    }

    printf("\nResult: %Iu\n", result);

    return 0;
}