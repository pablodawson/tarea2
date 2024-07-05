#include <stdio.h>
#include <stdlib.h>

void countingsort(Entrada a[], int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (max < a[i].rut) max = a[i].rut;
    }
    
    int* count = (int *)calloc(max + 1, sizeof(int));  
    Entrada* output = (Entrada *)malloc(size * sizeof(Entrada)); 

    for (int i = 0; i < size; i++) {
        count[a[i].rut]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[a[i].rut] - 1] = a[i];
        count[a[i].rut]--;
    }

    for (int i = 0; i < size; i++) {
        a[i] = output[i];
    }

    free(count);
    free(output);
}