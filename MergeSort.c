#include <stdio.h>
#define ENTRADAS_MAX 1000

int comparisons = 0;

int mergesort(Entrada a[], int i, int j);
void merge(Entrada a[], int i1, int j1, int i2, int j2);

int mergesort(Entrada a[], int i, int j)
{
    int mid;
    
    if (i < j)
    {
        mid = (i + j) / 2;
        mergesort(a, i, mid);    // left recursion
        mergesort(a, mid + 1, j); // right recursion
        merge(a, i, mid, mid + 1, j); // merging of two sorted sub-arrays
    }

    return comparisons;
}

void merge(Entrada a[], int i1, int j1, int i2, int j2)
{
    Entrada temp[ENTRADAS_MAX]; // array used for merging
    int i, j, k;
    i = i1; // beginning of the first list
    j = i2; // beginning of the second list
    k = 0;
    
    while (i <= j1 && j <= j2) // while elements in both lists
    {
        if (a[i].rut < a[j].rut)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
        
        comparisons+=3;
    }
    
    while (i <= j1){ // copy remaining elements of the first list
        temp[k++] = a[i++];
        comparisons++;
    }
    while (j <= j2) { // copy remaining elements of the second list
        temp[k++] = a[j++];
        comparisons++;
    }
    // Transfer elements from temp[] back to a[]
    for (i = i1, j = 0; i <= j2; i++, j++){ 
        a[i] = temp[j];
        comparisons++;
    }
}