#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// A common security method used for online banking is to ask the user for three random characters from a passcode.
// For example, if the passcode was 531278, they may ask for the 2nd, 3rd, and 5th characters; the expected reply would be : 317.
//
// The text file, keylog.txt, contains fifty successful login attempts.
//
// Given that the three characters are always asked for in order, analyse the file so as to determine the shortest possible secret passcode of unknown length.

#ifdef _WIN64
#define FILE_NAME "..\\..\\Task79\\p079_keylog.txt"
#else
#define FILE_NAME "..\\Task79\\p079_keylog.txt"
#endif
#define SEMICOLON '\n'


int main(int argc, char **argv)
{
    // Читаем данные из файла
    size_t file_size = 0;

    read_file(FILE_NAME, NULL, &file_size);
    char* file_data = (char*)malloc(sizeof(char) * (file_size + 1));
    read_file(FILE_NAME, file_data, &file_size);
    file_data[file_size] = '\0';

    // Считаем количество элементов в файле
    size_t size = 0;
    for (size_t i = 0; i < file_size; ++i)
        if (file_data[i] == SEMICOLON || file_data[i] == '\n')
            size++;

#ifdef _DEBUG
    printf("\nTotal answers: %Iu\n", size);
#endif

    //Помещаем элементы в массив
    size_t answer_size = 3;

    size_t* answers = (size_t*)malloc(sizeof(size_t) * size);

    for (size_t i = 0; i < size; ++i)
    {
        char tmp[100];

        strncpy_s(tmp, 100, file_data + (answer_size + 1) * i, answer_size);
        tmp[answer_size] = '\0';

        answers[i] = atoi(tmp);
    }

    free(file_data);

    // !!! Данный метод подходит только для набора чисел без повторений !!!

    size_t sequence[10][10] = { 0 };
    size_t used_digits[10]  = { 0 };

    for (size_t i = 0; i < size; ++i)
    {
        size_t current_number = answers[i];
        size_t current_digit_size = get_digitsize(current_number);

        char* str_current_number = (char*)malloc(sizeof(char) * (current_digit_size + 1));
        sprintf_s(str_current_number, current_digit_size + 1, "%Id", current_number);

        while (true)
        {
            if (current_number / 10 == 0)
            {
                used_digits[current_number] = 1;
                break;
            }
            else
            {
                size_t current_digit = current_number % 10;

                used_digits[current_digit] = 1;
               
                for (size_t digit_count = 0; digit_count < get_digitsize(current_number) - 1; ++digit_count)
                {
                    sequence[str_current_number[digit_count] - '0'][current_digit] = 1;
                }

                current_number /= 10;
            }
        }

        free(str_current_number);
    }
    
    size_t sums[10] = { 0 };
    size_t used_digits_count = 10;

    for (size_t i = 0; i < 10; ++i)
    {
        for (size_t j = 0; j < 10; ++j)
            sums[i] += sequence[i][j];

        if (!used_digits[i])
            used_digits_count--;
    }

    char* passcode = (char*)malloc(sizeof(char) * (used_digits_count + 1));
    size_t offset = 0;

    while (used_digits_count)
    {
        size_t max_sum   = 0;
        size_t max_digit = 0;

        for (size_t i = 0; i < 10; ++i)
        {
            if (used_digits[i])
            {
                if (sums[i] > max_sum)
                {
                    max_sum = sums[i];
                    max_digit = i;
                }
            }
            else
                continue;
        }

        passcode[offset] = max_digit + '0';
        offset++;

        used_digits[max_digit] = 0;
        used_digits_count--;
    }

    passcode[offset] = '\0';

    printf("\nResult: %s\n", passcode);

    free(passcode);

    return 0;
}