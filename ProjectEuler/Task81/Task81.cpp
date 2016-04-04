#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"


// In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and down,
// is indicated in bold red and is equal to 2427.
//
//      ⎛  131  673  234  103  18   ⎞
//      ⎜  201  96   342  965  150  ⎟
//      ⎜  630  803  746  422  111  ⎟
//      ⎜  537  699  497  121  956  ⎟
//      ⎝  805  732  524  37   331  ⎠
// 
// Find the minimal path sum, in matrix.txt(right click and "Save Link/Target As..."), a 31K text file containing a 80 by 80 matrix, 
// from the top left to the bottom right by only moving right and down.

#ifdef _WIN64
#define FILE_NAME "..\\..\\Task81\\p081_matrix.txt"
#else
#define FILE_NAME "..\\Task81\\p081_matrix.txt"
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

    // Считаем количество элементов в файле
    size_t size = 0;
    for (size_t i = 0; i < file_size; ++i)
        if (file_data[i] == SEMICOLON || file_data[i] == '\n')
            size++;

#ifdef _DEBUG
    printf("\nTotal elements: %Iu\n", size);
#endif

    size_t matrix_size = sqrt(size);

    //Помещаем элементы в массив
    size_t offset = 0;

    size_t** matrix = (size_t**)malloc(sizeof(size_t*) * matrix_size);
    for (size_t i = 0; i < matrix_size; ++i)
        matrix[i] = (size_t*)malloc(sizeof(size_t) * matrix_size);

    for (size_t i = 0; i < matrix_size; ++i)
    {
        for (size_t j = 0; j < matrix_size; ++j)
        {
            char* p1 = strchr(file_data + offset, SEMICOLON);

            if (j == matrix_size - 1)
                p1 = strchr(file_data + offset, '\n');

            p1[0] = '\0';

            matrix[i][j] = atoi(file_data + offset);

            offset = p1 - file_data + 1;
        }
    }

    free(file_data);

    //Вычисляем 

    size_t** sum_matrix = (size_t**)malloc(sizeof(size_t*) * matrix_size);
    for (size_t i = 0; i < matrix_size; ++i)
        sum_matrix[i] = (size_t*)malloc(sizeof(size_t) * matrix_size);

    for (int i = matrix_size - 1; i >= 0; --i)
    {
        for (int j = i; j >= 0; --j)
        {
            if (i == matrix_size - 1 && j == matrix_size - 1)
            {
                sum_matrix[i][j] = matrix[i][j];
                continue;
            }

            if (i == matrix_size - 1)
            {
                sum_matrix[i][j] = matrix[i][j] + sum_matrix[i][j + 1];
                sum_matrix[j][i] = matrix[j][i] + sum_matrix[j + 1][i];
            }
            else
            {
                sum_matrix[i][j] = matrix[i][j] + min(sum_matrix[i][j + 1], sum_matrix[i + 1][j]);
                sum_matrix[j][i] = matrix[j][i] + min(sum_matrix[j + 1][i], sum_matrix[j][i + 1]);
            }
        }
    }

    size_t result = matrix[0][0] + matrix[matrix_size - 1][matrix_size - 1];
    size_t i = 0;
    size_t j = 0;

    while (i != matrix_size - 1 && j != matrix_size - 1)
    {
        if (j == matrix_size - 1)
        {
            result += matrix[i + 1][j];
            i++;
            continue;
        }

        if (i == matrix_size - 1)
        {
            result += matrix[i][j + 1];
            j++;
            continue;
        }

        if (sum_matrix[i + 1][j] < sum_matrix[i][j + 1])
        {
            result += matrix[i + 1][j];
            i++;
        }
        else
        {
            result += matrix[i][j + 1];
            j++;
        }
    }

    printf("\n\nResult: %Iu\n", result);

    for (size_t i = 0; i < matrix_size; ++i)
    {
        free(matrix[i]);
        free(sum_matrix[i]);
    }

    free(matrix);
    free(sum_matrix);

    return 0;
}