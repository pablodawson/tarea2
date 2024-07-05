#include <stdio.h>
#include <stdlib.h>

int swapped = 0;
void swap(Entrada *a, Entrada *b)
{
    Entrada temp = *b;
    *b = *a;
    *a = temp;
}

int bubblesort(Entrada *a, int size)
{
    int swapped;
    int i;
    int comparisons = 0;

    for (i = 0; i < size - 1; i++)
    {
        comparisons+=1;
        swapped = 0;
        int j;
        for (j = 0; j < size - i - 1; j++)
        {
            comparisons+=2;
            if (a[j].rut > a[j + 1].rut)
            {
                swap(&a[j], &a[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0)
            break;
    }

    return comparisons;
}