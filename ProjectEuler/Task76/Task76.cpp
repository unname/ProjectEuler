#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// It is possible to write five as a sum in exactly six different ways :
//
//      4 + 1
//      3 + 2
//      3 + 1 + 1
//      2 + 2 + 1
//      2 + 1 + 1 + 1
//      1 + 1 + 1 + 1 + 1
//
// How many different ways can one hundred be written as a sum of at least two positive integers ?

int main(int argc, char **argv)
{
    size_t number = 100;

    // New solution method
    printf("\nNew solution method:\n");

    char** answers = (char**)malloc(sizeof(char*) * (number + 1));

    size_t default_size = 50;

    for (size_t i = 0; i < number + 1; ++i)
    {
        answers[i] = (char*)malloc(sizeof(char) * default_size);
        strcpy_s(answers[i], 2, "0");
    }

    strcpy_s(answers[0], 2, "1");

    //Вычисление
    p(number, &answers);

    sub_string(answers[number], "1", answers[number], &default_size);

    printf("\tResult: %s\n", answers[number]);

    //Освобождаем память

    for (size_t i = 0; i < number + 1; ++i)
        free(answers[i]);
    free(answers);


    // Old solution method

    size_t  set_size = number - 1;
    size_t* set = (size_t*)malloc(sizeof(size_t) * set_size);
    
    for (size_t i = 0; i < set_size; ++i)
        set[i] = i + 1;

    printf("\nOld solution method:\n");
    printf("\tResult: %Iu\n", p(number, set, set_size));

    free(set);

    return 0;
}