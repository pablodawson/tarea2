#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "entrada.h"

#include "BubbleSort.c"
#include "CountingSort.c"
#include "MergeSort.c"

#define ENTRADAS_MAX 1000
#define TAMANO_LINEA 100


void trim(char *str) {
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) {
        return;
    }
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\0';
}

void registrarInfo(const char *direccionArchivo, Entrada *entradas, int *numEntradas) {
    FILE *file = fopen(direccionArchivo, "r");
    if (file == NULL) {
        perror("Error abriendo el archivo de texto");
        return;
    }

    char line[TAMANO_LINEA];
    int index = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        
        line[strcspn(line, "\n")] = '\0';

        Entrada entrada;
        entrada.index = index;

        char *token = strtok(line, " ");

        while (token != NULL) {
            trim(token);
            if (strlen(token) == 8) {
                entrada.rut = atoi(token);
            } else if (strlen(token) == 3) {
                entrada.nota = atoi(token);
            } else if (strlen(token) == 6) {
                strcpy(entrada.sigla, token);
            } else {
                printf("\n No se pudo asignar %s", token);
            }
            token = strtok(NULL, " ");
        }
        
        entradas[index] = entrada;
        index++;
    }

    *numEntradas = index;

    fclose(file);
}

void imprimirInfo(Entrada entradas[], int numEntradas){
    for (int i = 0; i < numEntradas; i++) {
        printf("Index: %d, Rut: %d, Nota: %d, Sigla: %s\n",
               entradas[i].index, entradas[i].rut, entradas[i].nota, entradas[i].sigla);
    }
}

void escribirEntradasTxt(const char *direccionOutput, Entrada *entradas, int numEntradas) {

    FILE *file = fopen(direccionOutput, "w");
    if (file == NULL) {
        perror("Error haciendo el texto de output");
        return;
    }

    for (int i = 0; i < numEntradas; i++) {
        fprintf(file,  "%08d %s %03d\n",
                entradas[i].rut, entradas[i].sigla, entradas[i].nota);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <dir_archivo_txt> <id_algoritmo>\n", argv[0]);
        return 1;
    }

    const char *direccionArchivo = argv[1];

    Entrada entradas[ENTRADAS_MAX];
    int numEntradas = 0;

    // --- Registrar la informacion en un struct e imprimir en consola ---

    printf("\n --- Desordenado --- \n");
    registrarInfo(direccionArchivo, entradas, &numEntradas);
    imprimirInfo(entradas, 10);
    
    // --- Crear ordenado.txt ---

    const char *algorimoId = argv[2];
    int id = atoi(algorimoId);

    clock_t start_time = clock();
    if (id==0){
        // Bubblesort
        printf("\n --- Ordenado con BubbleSort: --- \n");
        bubblesort(entradas, numEntradas);
    } else if (id==1){
        // Countingsort
        printf("\n --- Ordenado con CountingSort: --- \n");
        countingsort(entradas, numEntradas);
    } else {
        // Mergesort
        printf("\n --- Ordenado con MergeSort: --- \n");
        mergesort(entradas, 0, numEntradas-1);
    }

    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Sort en %f segundos\n", elapsed_time);
    imprimirInfo(entradas, 10);
    escribirEntradasTxt("ordenado.txt", entradas, numEntradas);

    // --- Crear reporte de todos los algoritmos ---

    FILE *reporte = fopen("reporte.txt", "w");
    fprintf(reporte, "Para procesar: %d entradas\n", numEntradas);

    if (reporte == NULL) {
        perror("Error haciendo el texto de reporte");
        return 0;
    }

    // Empezar desordenado nuevamente

    // Bench Bubble Sort
    registrarInfo(direccionArchivo, entradas, &numEntradas);
    start_time = clock();
    bubblesort(entradas, numEntradas);
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    fprintf(reporte, "Tiempo de ejecucion Bubble Sort: %f segundos\n", elapsed_time);

    // Bench Counting Sort
    registrarInfo(direccionArchivo, entradas, &numEntradas);
    start_time = clock();
    countingsort(entradas, numEntradas);
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    fprintf(reporte, "Tiempo de ejecucion Counting Sort: %f segundos\n", elapsed_time);
    
    // Bench Merge Sort
    registrarInfo(direccionArchivo, entradas, &numEntradas);
    start_time = clock();
    mergesort(entradas, 0, numEntradas-1);
    elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    fprintf(reporte, "Tiempo de ejecucion Merge Sort: %f segundos\n", elapsed_time);
    
    fclose(reporte);

    return 0;
}