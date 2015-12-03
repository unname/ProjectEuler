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

                (*ulOut)++;
                break;
            }
        }
    }
}

void func2(size_t n1, size_t n2, size_t k, size_t *pOut, size_t *ulOut, bool start)
{
    if (start)
    {
        if (pOut)
        {
            pOut[0] = n1;
            pOut[1] = n2;

            pOut += 2;
        }

        *ulOut  = 2;
    }

    size_t current_value = n1 + n2;
    
    if (current_value >= k)
        return;

    if (pOut)
    {
        *pOut = current_value;
        pOut++;
    }

    (*ulOut)++;

    func2(n2, current_value, k, pOut, ulOut);
}