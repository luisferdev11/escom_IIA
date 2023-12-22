#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

int main() {
    int size = 10;  // Example size
    int* array = createArray(size);
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 100;
    }

    printf("Original array:\n");
    printArray(array, size);

    // For selection sort
    selectionSort(array, size, 1);
    printf("Selection sorted array:\n");
    printArray(array, size);

    // For merge sort (assuming array is reset or a new array is created)
    divide(array, size, 0);
    printf("Merge sorted array:\n");
    printArray(array, size);

    // insertionSort(array, size);
    printf("Insertion sorted array:\n");
    insertionSort(array, size, 1);
    printArray(array, size);

    destroyArray(array);
    return 0;
}