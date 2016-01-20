#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// The n'th term of the sequence of triangle numbers is given by, tn = ½n(n + 1); so the first ten triangle numbers are :
//
//      1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
//
// By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value.
// For example, the word value for SKY is 19 + 11 + 25 = 55 = t10.
// If the word value is a triangle number then we shall call the word a triangle word.
//
// Using words.txt(right click and 'Save Link/Target As...'), a 16K text file containing nearly two - thousand common English words, how many are triangle words ?

#ifdef _WIN64
#define FILE_NAME "..\\..\\Task42\\p042_words.txt"
#else
#define FILE_NAME "..\\Task42\\p042_words.txt"
#endif
#define SEMICOLON ','

int main(int argc, char **argv)
{
    // Читаем данные из файла
    size_t file_size = 0;

    read_file(FILE_NAME, NULL, &file_size);
    char* file_data = (char*)malloc(sizeof(char) * (file_size + 1));
    read_file(FILE_NAME, file_data, &file_size);
    file_data[file_size] = '\0';

#ifdef _DEBUG
    printf("\nFile value: %s\n", file_data);
#endif

    // Считаем количество элементов в файле
    size_t size = 0;
    for (size_t i = 0; i < file_size; ++i)
        if (file_data[i] == SEMICOLON)
            size++;
    if (size)
        size++;

#ifdef _DEBUG
    printf("\nTotal elements: %Iu\n", size);
#endif

    //Помещаем элементы в массив
    size_t offset = 0;

    char** words = (char**)malloc(sizeof(char*) * size);
    for (size_t i = 0; i < size; ++i)
    {
        char* p1 = strstr(file_data + offset, "\"") + 1;
        char* p2 = strstr(p1, "\"");

        offset = p2 - file_data + 1;

        words[i] = (char*)malloc(sizeof(char) * (p2 - p1 + 1));

        for (size_t j = 0; j < p2 - p1; ++j)
        {
            words[i][j] = p1[j];
        }
        words[i][p2 - p1] = '\0';
    }

    free(file_data);

#ifdef _DEBUG
    for (size_t i = 0; i < size; ++i)
        printf("Word[%Iu]: %s\n", i + 1, words[i]);
    printf("\n");
#endif

    // Проверяем является ли слово триугольным
    //
    // Number is triangle if and only if '8*x + 1' is square (получаем из 'n^2 + n - 2t = 0')

    size_t result = 0;

    for (size_t i = 0; i < size; ++i)
    {
        size_t sum = 0;

        for (size_t j = 0; words[i][j] != '\0'; ++j)
        {
            sum += words[i][j] - 'A' + 1;
        }

        size_t power = 0;
        test_power(sum * 8 + 1, nullptr, &power);
        
        if (power && power%2 == 0)
            result++;
    }

    printf("\nResult: %Iu\n", result);

    //Освобождаем память
    for (size_t i = 0; i < size; ++i)
        free(words[i]);
    free(words);

    return 0;
}
