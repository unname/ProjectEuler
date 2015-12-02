#include "euler_functions.h"

void func1(size_t k1, size_t k2, size_t *pOut, size_t *ulOut, size_t x, ...)
{
    size_t *pIn;
    *ulOut = 0;

    for (size_t i = k1; i <= k2; i++)
    {
        //Начинаем с первого делителя
        pIn = &x;

        while (*pIn)
        {
            if (i % *pIn)
            {
                pIn++;
            }
            else
            {
                if (pOut)
                {
                    *pOut = i;
                    pOut++;
                }

                *ulOut += 1;
                break;
            }
        }
    }
}