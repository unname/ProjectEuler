#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// It is possible to show that the square root of two can be expressed as an infinite continued fraction.
//
//          √2 = 1 + 1/(2 + 1/(2 + 1/(2 + ...))) = 1.414213...
//
// By expanding this for the first four iterations, we get :
//
// 1 + 1/2 = 3/2 = 1.5
// 1 + 1/(2 + 1/2) = 7/ 5 = 1.4
// 1 + 1/(2 + 1/(2 + 1/2)) = 17 / 12 = 1.41666...
// 1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41 / 29 = 1.41379...
//
// The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, is the first example
// where the number of digits in the numerator exceeds the number of digits in the denominator.
//
// In the first one-thousand expansions, how many fractions contain a numerator with more digits than denominator ?

int main(int argc, char **argv)
{
    size_t upper_limit = 1000;
    size_t result = 0;

    char* numerator = (char*)malloc(sizeof(char) * 2);
    sprintf_s(numerator, 2,"%Iu", 3);

    char* denominator = (char*)malloc(sizeof(char) * 2);
    sprintf_s(denominator, 2, "%Iu", 2);

    for (size_t i = 0; i < upper_limit; ++i)
    {
        if (strlen(numerator) > strlen (denominator))
            result++;

        size_t length = 0;

        //numerator += denominator;
        sum_string(numerator, denominator, NULL, &length);
        numerator = (char*)realloc(numerator, sizeof(char) * length);
        sum_string(numerator, denominator, numerator, &length);
      
        //denominator += numerator;
        sum_string(denominator, numerator, NULL, &length);
        denominator = (char*)realloc(denominator, sizeof(char) * length);
        sum_string(denominator, numerator, denominator, &length);

        //size_t n = numerator;
        //numerator = denominator;
        //denominator = n;
        char* tmp = (char*)malloc(sizeof(char) * (strlen(numerator) + 1));
        strcpy_s(tmp, strlen(numerator) + 1, numerator);

        numerator = (char*)realloc(numerator, sizeof(char) * (strlen(denominator) + 1));
        strcpy_s(numerator, strlen(denominator) + 1, denominator);

        denominator = (char*)realloc(denominator, sizeof(char) * (strlen(tmp) + 1));
        strcpy_s(denominator, strlen(tmp) + 1, tmp);

        free(tmp);
    }

    printf("\nResult: %Iu\n", result);

    free(numerator);
    free(denominator);

    return 0;
}