(1) Reseña:

Implementacion y benchmark de algoritmos de sorting.
Se usaron los algoritmos:
- Bubble Sort, de complejidad O(n2)
- Counting Sort, de complejidad O(d(n+k))
- Merge Sort, de complejidad O(n log(n))

Las implementaciones de estos algorimos vienen de https://github.com/diptangsu/Sorting-Algorithms/tree/master.
Estas se adaptaron para funcionar con el struct propuesto, en lugar de arrays.

(2) Condiciones de compilación:
No se requieren librerías adicionales.

(3) Instrucciones de compilación:
Una vez dentro de la carpeta principal:
cd (direccion)

Simplemente compilar con gcc:
gcc main.c

Instrucciones de uso:
./a.out <dir_archivo_txt> <id_algoritmo>
Donde <dir_archivo_txt> es la direccion del archivo de prueba.
Y <id_algoritmo> es con que algoritmo se crea el archivo "ordenado.txt". Donde 0 es BubbleSort, 1 es CountingSort y 2 es MergeSort.

(4)
Pablo Dawson A.
201921034-3