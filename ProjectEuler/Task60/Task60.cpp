#include <stdlib.h>
#include <iostream>
#include <windows.h>

#include "euler_functions.h"


// The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime.
// For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.
//
// Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.

#define thread_printf(mutex, scrn_x, scrn_y, ...) WaitForSingleObject(mutex, INFINITE); SetCarriege(scrn_x, scrn_y); printf(__VA_ARGS__); GetCarriege(&scrn_x, &scrn_y); ReleaseMutex(mutex);

struct SearchParams
{
    size_t screen_y;
    size_t screen_x;

    size_t* PrimesPool;
    size_t  primes_count;
    
    size_t search_count;
    
    size_t mask_offset_1;
    size_t mask_offset_2;
    size_t mask_offset_3;

    size_t max_primes_sum;

    size_t max_offset;
    
    HANDLE mutex;
    HANDLE log_mutex;

    static size_t** Tetrads;
    static size_t   tetrads_count;
} s;



size_t** SearchParams::Tetrads      = nullptr;
size_t SearchParams::tetrads_count  = 0;

static size_t ScreenOffset = 0;

void SetScreenOffset()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { 0 };
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

    ScreenOffset = consoleInfo.dwCursorPosition.Y;
}

void SetCarriege(size_t x, size_t y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { 0 };
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

    consoleInfo.dwCursorPosition.X = x;
    consoleInfo.dwCursorPosition.Y = ScreenOffset + y;

    SetConsoleCursorPosition(consoleHandle, consoleInfo.dwCursorPosition);
}

void GetCarriege(size_t* x, size_t* y)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { 0 };
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);

    if (x)
        *x = consoleInfo.dwCursorPosition.X;
    if (y)
        *y = consoleInfo.dwCursorPosition.Y - ScreenOffset;

    SetConsoleCursorPosition(consoleHandle, consoleInfo.dwCursorPosition);
}


DWORD WINAPI TetradsSearhing(PVOID pParam)
{
    SearchParams* p = (SearchParams*)pParam;

    size_t* current_set = (size_t*)malloc(sizeof(size_t) * p->search_count);

    for (int set_count = 0, offset = 0; offset < p->max_offset; ++offset)
    {
        if (p->PrimesPool[offset] > p->max_primes_sum / 5)
            ExitThread(0);

        thread_printf(p->log_mutex, p->screen_x, p->screen_y, "\r\t\t\t\t\t\t\t");

        thread_printf(p->log_mutex, p->screen_x, p->screen_y, "\rSearch sets: %Iu of %Iu  Set:", offset + 1, p->max_offset);
  
        memset(current_set, 0, sizeof(size_t) * p->search_count);

        set_count = 1;
        current_set[0] = p->PrimesPool[offset];
        thread_printf(p->log_mutex, p->screen_x, p->screen_y, " %Iu", current_set[0]);
  
        size_t founded_count = 0;

        size_t sum = p->PrimesPool[offset];

        for (size_t i = offset + 1; set_count < p->search_count & i < p->primes_count; ++i)
        {
            bool skip = true;

            if (set_count == 1 && founded_count == p->mask_offset_1) 
                skip = false;

            if (set_count == 2 && founded_count == p->mask_offset_2)
                skip = false;

            if (set_count == 3 && founded_count == p->mask_offset_3)
                skip = false;

            for (size_t j = 0; j < set_count; ++j)
            {
                if (!test_prime(current_set[j] * pow(10, get_digitsize(p->PrimesPool[i])) + p->PrimesPool[i]))
                    break;

                if (!test_prime(p->PrimesPool[i] * pow(10, get_digitsize(current_set[j])) + current_set[j]))
                    break;

                if (p->PrimesPool[i] > p->max_primes_sum / (5 - set_count))
                    goto next_set;

                if (j == set_count - 1)
                {
                    founded_count++;

                    if (!skip)
                    {
                        founded_count = 0;

                        sum += p->PrimesPool[i];

                        if (sum > p->max_primes_sum)
                            goto next_set;

                        set_count++;
                        current_set[set_count - 1] = p->PrimesPool[i];

                        thread_printf(p->log_mutex, p->screen_x, p->screen_y, " %Iu", current_set[set_count - 1]);

                        break;
                    }
                }
            }
        }

        if (set_count == p->search_count)
        {
            WaitForSingleObject(p->mutex, INFINITE);

            p->tetrads_count++;

            p->Tetrads = (size_t**)realloc(p->Tetrads, sizeof(size_t*) * p->tetrads_count);
            p->Tetrads[p->tetrads_count - 1] = (size_t*)malloc(sizeof(size_t) * p->search_count);

            for (size_t i = 0; i < set_count; ++i)
                p->Tetrads[p->tetrads_count - 1][i] = current_set[i];

            ReleaseMutex(p->mutex);
        }

    next_set:;
    }

    free(current_set);

    ExitThread(0);
}

int main(int argc, char **argv)
{
#ifdef _WIN64
    
    const size_t max_threads_count = 50;

    HANDLE hThreads[max_threads_count];
    SearchParams ParamsArray[max_threads_count];

    //Searching seed's: -------------------------------------------------------- 

    const size_t max_primes_count = 5000;
    size_t primes[max_primes_count];

    const size_t max_primes_sum = 50000; // 5000nd prime < 50000

    //Маски нужны, чтобы выбирать какое именно по счёту, подходящее по условию, число включать в сет
    const size_t mask_offset_1_limit = 50;
    const size_t mask_offset_2_limit = 10; 
    const size_t mask_offset_3_limit = 5;

    //--------------------------------------------------------------------------


    const size_t set_size = 5;
    const size_t offset_limit = max_primes_count - 5;

    //Набор простых чисел для поиска групп
    for (size_t n = 3, i = 0; i < max_primes_count; n += 2)
    {
        if (test_prime(n))
        {
            primes[i] = n;
            i++;
        }
    }

    size_t mask_offset_1 = 0;
    size_t mask_offset_2 = 0;
    size_t mask_offset_3 = 0;

    bool searching_complete = false;

    printf("\n This task recursivly searching %Iu-primes sets, print sum if it was founded and continue searching", set_size);

new_cycle:
    
    //Ищем различные наборы по 4 числа удовлетворяющих условию

    HANDLE hMutex    = CreateMutex(NULL, FALSE, NULL);
    HANDLE hLogMutex = CreateMutex(NULL, FALSE, NULL);

    for (size_t threads_count = 0; threads_count < max_threads_count; ++threads_count)
    {
        ParamsArray[threads_count].mutex          = hMutex;
        ParamsArray[threads_count].log_mutex      = hLogMutex;

        ParamsArray[threads_count].screen_x       = 0;
        ParamsArray[threads_count].screen_y       = threads_count;

        ParamsArray[threads_count].max_offset     = offset_limit;
        ParamsArray[threads_count].PrimesPool     = primes;
        ParamsArray[threads_count].primes_count   = max_primes_count;
        ParamsArray[threads_count].search_count   = set_size - 1;

        ParamsArray[threads_count].max_primes_sum = max_primes_sum;

        ParamsArray[threads_count].mask_offset_1  = mask_offset_1;
        ParamsArray[threads_count].mask_offset_2  = mask_offset_2;
        ParamsArray[threads_count].mask_offset_3  = mask_offset_3;


        if (!threads_count)
        {
            printf("\n\n   Search next set primes. Mask: %Iu %Iu %Iu \n\n", mask_offset_1, mask_offset_2, mask_offset_3);
            SetScreenOffset();
        }

        if (mask_offset_1 < mask_offset_1_limit)
            mask_offset_1++;
        else
        {
            mask_offset_1 = 0;

            if (mask_offset_2 < mask_offset_2_limit)
                mask_offset_2++;
            else
            {
                mask_offset_2 = 0;
                
                if (mask_offset_3 < mask_offset_3_limit)
                    mask_offset_3++;
                else
                {
                    printf("\n\n\t -= Checking Complete =- \n\n");

                    searching_complete = true;

                    getchar();
                    break;
                }

            }
        }

        hThreads[threads_count] = CreateThread(NULL, 0, &TetradsSearhing, &ParamsArray[threads_count], 0, NULL);
    }

    WaitForMultipleObjects(max_threads_count, hThreads, TRUE, INFINITE);

    SetCarriege(0, max_threads_count + 2);


    CloseHandle(hMutex);
    CloseHandle(hLogMutex);

    printf("Total sets[4]: %Iu\n", SearchParams::tetrads_count);

    for (size_t i = 0; i < SearchParams::tetrads_count; ++i)
    {
        printf("Set(%Iu):", i + 1);
        for (size_t j = 0; j < set_size - 1; ++j)
            printf(" %Iu", SearchParams::Tetrads[i][j]);

        printf("\n");
    }

    printf("\n");

    //Ищем 5-ый элемент для уже найденных сетов
    
    //Перебираем все сеты по 4
    for (size_t sets_count = 0; sets_count < SearchParams::tetrads_count; ++sets_count)
    {
        printf("\r\t\t\t\t\t\t\t\t\t\t\t");
        printf("\rSearch 5th set number: %Iu of %Iu  Set:", sets_count + 1, SearchParams::tetrads_count);

        for (size_t i = 0; i < set_size - 1; ++i)
        {
            printf(" %Iu", SearchParams::Tetrads[sets_count][i]);
        }

        size_t result = 0;

        //Перебираем простые числа
        for (size_t primes_count = 0; primes_count < max_primes_count; ++primes_count)
        {
            if (primes[primes_count] <= SearchParams::Tetrads[sets_count][3])
                continue;

            //Сравниваем элементы сета с простым числом
            for (size_t set_count = 0; set_count < set_size - 1; ++set_count)
            {
                if (!test_prime(SearchParams::Tetrads[sets_count][set_count] * pow(10, get_digitsize(primes[primes_count])) + primes[primes_count]))
                    break;

                if (!test_prime(primes[primes_count] * pow(10, get_digitsize(SearchParams::Tetrads[sets_count][set_count])) + SearchParams::Tetrads[sets_count][set_count]))
                    break;

                //Нашли 5-ый элемент
                if (set_count == set_size - 2)
                {
                    printf(" %Iu", primes[primes_count]);

                    for (size_t i = 0; i < set_size - 1; ++i)
                        result += SearchParams::Tetrads[sets_count][i];

                    result += primes[primes_count];

                    //goto end; 
                    printf("\nResult: %Iu\n", result);
                    getchar();
                }
            }
        }
    }
 
    if (SearchParams::Tetrads)
        free(SearchParams::Tetrads);

    SearchParams::Tetrads = nullptr;
    SearchParams::tetrads_count = 0;

    if (!searching_complete)
        goto new_cycle;
#endif

    return 0;
}