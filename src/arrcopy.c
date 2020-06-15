#include "arrcopy.h"

void CopyArray(const int *old, int *new, int size)
{
    for (int i = 0; i < size; i++)
    {
        *new = *old;
        old++;
        new++;
    }
}
