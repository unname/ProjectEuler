#include <stdlib.h>
#include <iostream>
#include "windows.h"

#include "euler_functions.h"

// The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the left column and finishing in any cell in the right column,
// and only moving up, down, and right, is indicated in red and bold; the sum is equal to 994.
//
//      ⎛  131  673  234  103  18   ⎞
//      ⎜  201  96   342  965  150  ⎟
//      ⎜  630  803  746  422  111  ⎟
//      ⎜  537  699  497  121  956  ⎟
//      ⎝  805  732  524  37   331  ⎠
// 
//Find the minimal path sum, in matrix.txt(right click and "Save Link/Target As..."), a 31K text file containing a 80 by 80 matrix, from the left column to the right column.

#ifdef _WIN64
#define FILE_NAME "..\\..\\Task83\\p083_matrix.txt"
#else
#define FILE_NAME "..\\Task83\\p083_matrix.txt"
#endif
#define SEMICOLON ','

void check_nearest_elements(size_t** sum_matrix, size_t** matrix, size_t matrix_size,size_t i, size_t j, size_t parrent)
{
    bool check_up       = true;
    bool check_down     = true;
    bool check_left     = true;
    bool check_right    = true;

    size_t previous_sum = sum_matrix[i][j];

    if (i > matrix_size - 1 || j > matrix_size - 1)
        return;

    if (i == 0 && j == 0)
        return;

    if (i == matrix_size - 1 && j == matrix_size - 1)
        return;

    size_t min_value = sum_matrix[i][j] - matrix[i][j];
    
    if (i > 0 && sum_matrix[i - 1][j] > 0)
        min_value = min(min_value, sum_matrix[i - 1][j]);

    if (i < matrix_size - 1 && sum_matrix[i + 1][j] > 0)
        min_value = min(min_value, sum_matrix[i + 1][j]);

    if (j > 0 && sum_matrix[i][j - 1] > 0)
        min_value = min(min_value, sum_matrix[i][j - 1]);

    if (j < matrix_size - 1 && sum_matrix[i][j + 1] > 0)
        min_value = min(min_value, sum_matrix[i][j + 1]);

    sum_matrix[i][j] = matrix[i][j] + min_value;

    if (sum_matrix[i][j] != previous_sum)
    {
        if (i > 0)
            if (min_value == sum_matrix[i - 1][j] || sum_matrix[i - 1][j] == 0)
                check_up = false;

        if (i < matrix_size - 1)
            if (min_value == sum_matrix[i + 1][j] || sum_matrix[i + 1][j] == 0)
                check_down = false;

        if (j > 0)
            if (min_value == sum_matrix[i][j - 1] || sum_matrix[i][j - 1] == 0)
                check_left = false;

        if (j < matrix_size - 1)
            if (min_value == sum_matrix[i][j + 1] || sum_matrix[i][j + 1] == 0)
                check_right = false;

        switch (parrent)
        {
        case 1:
            check_up = false;
            break;
        case 2:
            check_down = false;
            break;
        case 3:
            check_left = false;
            break;
        case 4:
            check_right = false;
            break;
        default:
            break;
        }

        if (i > 0 && check_up)
            check_nearest_elements(sum_matrix, matrix, matrix_size, i - 1, j, 2);
        if (i < matrix_size - 1 && check_down)
            check_nearest_elements(sum_matrix, matrix, matrix_size, i + 1, j, 1);
        if (j > 0 && check_left)
            check_nearest_elements(sum_matrix, matrix, matrix_size, i, j - 1, 4);
        if (j < matrix_size - 1 && check_right)
            check_nearest_elements(sum_matrix, matrix, matrix_size, i, j + 1, 3);
    }
}

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

    //Инициализация начальных параметров
    size_t** sum_matrix = (size_t**)malloc(sizeof(size_t*) * matrix_size);
    for (size_t i = 0; i < matrix_size; ++i)
    {
        sum_matrix[i] = (size_t*)malloc(sizeof(size_t) * matrix_size);

        for (size_t j = 0; j < matrix_size; ++j)
            sum_matrix[i][j] = 0;
    }

    sum_matrix[0][0] = matrix[0][0];

    for (size_t i = 1; i < matrix_size; ++i)
    {
        sum_matrix[i][0] = matrix[i][0] + sum_matrix[i - 1][0];
        sum_matrix[0][i] = matrix[0][i] + sum_matrix[0][i - 1];
    }

    //Вычисляем 
    for (size_t i = 1; i < matrix_size; ++i)
    {
        for (size_t j = 1; j < matrix_size; ++j)
        {
            size_t min = min(sum_matrix[i - 1][j], sum_matrix[i][j - 1]);

            sum_matrix[i][j] = matrix[i][j] + min;

            if (min == sum_matrix[i - 1][j])
                check_nearest_elements(sum_matrix, matrix, matrix_size, i, j - 1, 4);
            else
                check_nearest_elements(sum_matrix, matrix, matrix_size, i - 1, j, 2);
        }
    }

    printf("\n\nResult: %Iu\n", sum_matrix[matrix_size - 1][matrix_size - 1]);

    for (size_t i = 0; i < matrix_size; ++i)
    {
        free(matrix[i]);
        free(sum_matrix[i]);
    }

    free(matrix);
    free(sum_matrix);

    return 0;
}