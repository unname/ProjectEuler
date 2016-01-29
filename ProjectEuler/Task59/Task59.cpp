#include <stdlib.h>
#include <iostream>

#include "euler_functions.h"


// Each character on a computer is assigned a unique code and the preferred standard is ASCII(American Standard Code for Information Interchange).
// For example, uppercase A = 65, asterisk(*) = 42, and lowercase k = 107.
//
// A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value, taken from a secret key.
// The advantage with the XOR function is that using the same encryption key on the cipher text, restores the plain text;
// 
//      for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.
//
// For unbreakable encryption, the key is the same length as the plain text message, and the key is made up of random bytes.
// The user would keep the encrypted message and the encryption key in different locations, and without both "halves", it is impossible to decrypt the message.
//
// Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key.
// If the password is shorter than the message, which is likely, the key is repeated cyclically throughout the message.
// The balance for this method is using a sufficiently long password key for security, but short enough to be memorable.
//
// Your task has been made easy, as the encryption key consists of three lower case characters.
// Using cipher.txt(right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes,
// and the knowledge that the plain text must contain common English words, decrypt the message and find the sum of the ASCII values in the original text.

#ifdef _WIN64
#define FILE_NAME "..\\..\\Task59\\p059_cipher.txt"
#else
#define FILE_NAME "..\\Task59\\p059_cipher.txt"
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
        if (file_data[i] == SEMICOLON)
            size++;
    if (size)
        size++;

#ifdef _DEBUG
    printf("\nTotal symbols: %Iu\n", size);
#endif

    //Помещаем элементы в массив
    char* offset = file_data;

    size_t* symbols = (size_t*)malloc(sizeof(size_t) * size);

    for (size_t i = 0; i < size; ++i)
    {
        char* semicolon = strchr(offset, SEMICOLON);

        if (i != size - 1)
        {
            offset[semicolon - offset] = '\0';
        }

        symbols[i] = atoi(offset);
        offset += semicolon - offset + 1;
    }

    free(file_data);

    //---------------------------------------------
    //         Расшифровываем сообщение
    //---------------------------------------------

    //Предполагаем, что самый частовстречающийся символ пробел ' '
    //Проверяем все самые часыте варианты, пока не заполнятся все символы ключа

    const size_t key_size = 3;
    const size_t key_crusher = ' ';

    size_t key[key_size] = { 0 };

    //Получаем массив частот символов (+ упорядоченный массив частот)
    size_t max_cipher_code = 0;

    for (size_t i = 0; i < size; ++i)
    {
        if (symbols[i] > max_cipher_code)
            max_cipher_code = symbols[i];
    }

    size_t freq_size = max_cipher_code + 1;

    size_t* freq = (size_t*)malloc(sizeof(size_t) * freq_size);
    size_t* sort_freq = (size_t*)malloc(sizeof(size_t) * freq_size);

    memset(freq, 0, sizeof(size_t) * freq_size);

    for (size_t i = 0; i < size; ++i)
    {
        freq[symbols[i]]++;
    }

    memcpy(sort_freq, freq, freq_size * sizeof(size_t));
    sort(sort_freq, freq_size, true);

    //Итеративное вычисление символов ключа
    size_t symbols_complete = 0;
    size_t current_symbol = 0;

    while (symbols_complete != key_size)
    {
        for (size_t i = 0; i < freq_size; ++i)
        {
            if (freq[i] == sort_freq[symbols_complete])
                current_symbol = i;
        }

#ifdef _DEBUG 
        printf("\nNext most frequent symbol code: %Iu\n", current_symbol);
#endif

        //Определим самое частое смещение current_symbol в тексте
        //такое же смещение будет и в ключе

        size_t offsets[key_size] = { 0 };

        for (size_t i = 0; i < size; ++i)
        {
            if (symbols[i] == current_symbol)
                offsets[i % key_size]++;
        }

        size_t key_offset = 0;
        size_t max_offset = 0;

        for (size_t i = 0; i < key_size; ++i)
        {
            if (offsets[i] > max_offset)
            {
                max_offset = offsets[i];
                key_offset = i;
            }
        }

        if (key[key_offset] == 0)
        {
            key[key_offset] = current_symbol ^ key_crusher;
            symbols_complete++;

#ifdef _DEBUG 
            printf("Key %Iu-symbol is '%c'\n", key_offset + 1, key[key_offset]);
#endif
        }
    }

    free(freq);
    free(sort_freq);

#ifdef _DEBUG 
    printf("\nKey was found: \"");
    for (size_t i = 0; i < key_size; ++i)
    {
        printf("%c", key[i]);
    }
    printf("\"\n");
#endif

    //Получаем оригинальное сообщение
    size_t result = 0;
    char* message = (char*)malloc(sizeof(char) * (size + 1));

    for (size_t i = 0; i < size; ++i)
    {
        message[i] = symbols[i] ^ key[i % 3];
        result += message[i];
    }

    message[size] = '\0';

#ifdef _DEBUG
    printf("\nOriginal text: \"%s\"\n", message);
#endif
    
    printf("\nResult: %Iu\n", result);

    return 0;
}