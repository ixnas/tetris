#include "array_tools.h"

void CopyArray(const int* old, int* new, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		*(new + i) = *(old + i);
	}
}

void SortArray(int* array, int size)
{
	int i, j;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - 1; j++)
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