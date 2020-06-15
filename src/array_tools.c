#include "array_tools.h"

void CopyArray(const int *old, int *new, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(new + i) = *(old + i);
    }
}

void SortArray(int *array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (*(array + j) > *(array + j + 1))
            {
                int a = *(array + j);
                *(array + j) = *(array + j + 1);
                *(array + j + 1) = a;
            }
        }
    }
}