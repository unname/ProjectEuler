#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"

// Let p(n) represent the number of different ways in which n coins can be separated into piles.
// For example, five coins can be separated into piles in exactly seven different ways, so p(5) = 7.
//
//      OOOOO
//      OOOO   O
//      OOO   OO
//      OOO   O   O
//      OO   OO   O
//      OO   O   O   O
//      O   O   O   O   O
//
// Find the least value of n for which p(n) is divisible by one million.

void cut_string_number(char** string, size_t new_length, bool append)
{
    size_t length = strlen(*string);

    if (new_length == length)
        return;

    if (new_length > length)
    {
        //ƒобавл€ем до нужной длины
        *string = (char*)realloc(*string, sizeof(char) * (new_length + 1));

        for (size_t i = 0; i < new_length; ++i)
        {
            (*string)[new_length - i] = (*string)[new_length - 1 - i];
        }

        for (size_t i = 1; i < new_length - length; ++i)
        {
            (*string)[i] = '0';
        }

        (*string)[0] = '1';
    }
    else
    {
        //—окращаем до нужной длины
        strcpy_s(*string, length + 1, *string + (length - new_length));

        char* tmp = (char*)malloc(sizeof(char) * (new_length + 1));
        strcpy_s(tmp, new_length + 1, *string);
        free(*string);
        *string = tmp;

        if ((*string)[0] == '0')
        {
            //если полученное число начинаетс€ с нул€, то добавл€ем ещЄ один старший разр€д
            if (append)
            {
                new_length++;

                *string = (char*)realloc(*string, sizeof(char) * (new_length + 1));

                for (size_t i = 0; i < new_length; ++i)
                {
                    (*string)[new_length - i] = (*string)[new_length - 1 - i];
                }

                (*string)[0] = '1';
            }
            //убераем нули из начала числа
            else
            {
                for (size_t i = 0; i < new_length; ++i)
                {
                    if ((*string)[0] == '0')
                    {
                        strcpy_s(*string, new_length + 1 - i, *string + 1);

                        char* tmp = (char*)malloc(sizeof(char) * (new_length - i));
                        strcpy_s(tmp, new_length - i, *string);
                        free(*string);
                        *string = tmp;
                    }
                    else
                        break;
                }
            }
        }
    }
}

int main(int argc, char **argv)
{

#ifdef _WIN64
    size_t start_value = 60;

    char expect_ending[] = "000000";
    size_t expect_size = strlen(expect_ending);

    char** answers = (char**)malloc(sizeof(char*) * start_value);

    for (size_t i = 0; i < start_value; ++i)
    {
        answers[i] = (char*)malloc(sizeof(char) * 2);
        strcpy_s(answers[i], 2, "0");
    }

    strcpy_s(answers[0], 2, "1");
    
    for (size_t n = start_value; ; ++n)
    {
#ifdef _DEBUG
        printf("\rn: %Iu", n);
#endif
        answers = (char**)realloc(answers, sizeof(char*) * (n + 1));
        answers[n] = (char*)malloc(sizeof(char) * 2);
        strcpy_s(answers[n], 2, "0");

        p(n, &answers);

#ifdef _DEBUG
        printf("  (%s)", answers[n] + strlen(answers[n]) - 6);
#endif
        if (n > 61)
        {
            cut_string_number(&answers[n - 1], expect_size, false);
            cut_string_number(&answers[n], expect_size + 3, true);
        }

        if (!strcmp(answers[n] + strlen(answers[n]) - 6, expect_ending))
        {
            printf("\n\nResult: %Iu\n", n);

            for (size_t i = 0; i <= n; ++i)
                free(answers[i]);
            free(answers);

            break;
        }
    }
#endif

    return 0;
}