#include "arrcopy.h"

void CopyArray(const bool *old, bool *new, const char size)
{
    for (char i = 0; i < size; i++)
    {
        *new = *old;
        old++;
        new++;
    }
}
