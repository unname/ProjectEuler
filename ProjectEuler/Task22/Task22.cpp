#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Using names.txt(right click and 'Save Link/Target As...'), a 46K text file containing over five - thousand first names, begin by sorting it into alphabetical order.Then working out the alphabetical value for each name, multiply this value by its alphabetical position in the list to obtain a name score.
//
// For example, when the list is sorted into alphabetical order, COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list.So, COLIN would obtain a score of 938 × 53 = 49714.
//
// What is the total of all the name scores in the file ?

#ifdef _WIN64
#define FILE_NAME "..\\..\\Task22\\p022_names.txt"
#else
#define FILE_NAME "..\\Task22\\p022_names.txt"
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

	char** names = (char**)malloc(sizeof(char*) * size);
	for (size_t i = 0; i < size; ++i)
	{
		char* p1 = strstr(file_data + offset, "\"") + 1;
		char* p2 = strstr(p1, "\"");

		offset = p2 - file_data + 1;

		names[i] = (char*)malloc(sizeof(char) * (p2 - p1 + 1));

		for (size_t j = 0; j < p2 - p1; ++j)
		{
			names[i][j] = p1[j];
		}
		names[i][p2 - p1] = '\0';
	}

	free(file_data);

#ifdef _DEBUG
	for (size_t i = 0; i < size; ++i)
		printf("Name[%Iu]: %s\n", i + 1, names[i]);
	printf("\n");
#endif

	// Сортируем массив
	sort(names, size);

#ifdef _DEBUG
	for (size_t i = 0; i < size; ++i)
		printf("Name[%Iu]: %s\n", i + 1, names[i]);
	printf("\n");
#endif

	// Считаем общее количество 'очков'
	size_t scores = 0;

	for (size_t i = 0; i < size; ++i)
	{
		size_t sum = 0;

		for (size_t j = 0; names[i][j] != '\0'; ++j)
		{
			sum += names[i][j] - 'A' + 1;
		}

		scores += sum * (i + 1);
	}

	printf("\nResult: %Iu\n", scores);

	//Освобождаем память
	for (size_t i = 0; i < size; ++i)
		free(names[i]);
	free(names);

	return 0;
}