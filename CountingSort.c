#include <stdio.h>
#include <stdlib.h>

int countingsort(Entrada a[], int size) {
    int max = 0;
    int i;
    int comparisons = 0;

    for (i = 0; i < size; i++) {
        if (max < a[i].rut) max = a[i].rut;
        comparisons++;
    }
    
    int* count = (int *)calloc(max + 1, sizeof(int));  
    Entrada* output = (Entrada *)malloc(size * sizeof(Entrada)); 

    for (i = 0; i < size; i++) {
        comparisons++;
        count[a[i].rut]++;
    }

    for (i = 1; i <= max; i++) {
        comparisons++;
        count[i] += count[i - 1];
    }

    for (i = size - 1; i >= 0; i--) {
        comparisons++;
        output[count[a[i].rut] - 1] = a[i];
        count[a[i].rut]--;
    }

    for (i = 0; i < size; i++) {
        comparisons++;
        a[i] = output[i];
    }

    free(count);
    free(output);

    return comparisons;
}