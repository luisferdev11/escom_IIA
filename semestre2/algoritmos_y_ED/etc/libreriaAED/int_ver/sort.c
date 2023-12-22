#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Creates an array with dynamic memory allocation
int* createArray(int size) {
    int* array = (int*)calloc(size, sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return array;
}

// Destroys a dynamically allocated array
void destroyArray(int* array) {
    free(array);
}

// Performs selection sort on the array
void selectionSort(int* array, int size, int isAscending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((isAscending && array[j] < array[i]) || (!isAscending && array[j] > array[i])) {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

// Divides the array for merge sort
void divide(int* array, int size, int isAscending) {
    if (size > 1) {
        int mid = size / 2;
        int* leftArray = createArray(mid);
        int* rightArray = createArray(size - mid);

        for (int i = 0; i < mid; i++) {
            leftArray[i] = array[i];
        }

        for (int i = mid; i < size; i++) {
            rightArray[i - mid] = array[i];
        }

        divide(leftArray, mid, isAscending);
        divide(rightArray, size - mid, isAscending);

        merge(leftArray, mid, rightArray, size - mid, array, isAscending);

        destroyArray(leftArray);
        destroyArray(rightArray);
    }
}

// Merges two subarrays for merge sort
void merge(int* leftArray, int leftSize, int* rightArray, int rightSize, int* mergedArray, int isAscending) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if ((isAscending && leftArray[i] < rightArray[j]) || (!isAscending && leftArray[i] > rightArray[j])) {
            mergedArray[k++] = leftArray[i++];
        } else {
            mergedArray[k++] = rightArray[j++];
        }
    }

    while (i < leftSize) {
        mergedArray[k++] = leftArray[i++];
    }

    while (j < rightSize) {
        mergedArray[k++] = rightArray[j++];
    }
}

// Performs insertion sort on the array
void insertionSort(int* array, int size, int isAscending) {
    for (int i = 1; i < size; i++) {
        int aux = array[i];
        int j = i - 1;
        while (j >= 0 && ((isAscending && array[j] > aux) || (!isAscending && array[j] < aux))) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = aux;
    }
}

// Prints the array
void printArray(const int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
