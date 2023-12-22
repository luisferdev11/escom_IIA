#include "sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* createArray(size_t numElements, size_t size) {
    void* array = calloc(numElements, size);
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return array;
}

void destroyArray(void* array) {
    free(array);
}

void selectionSort(void* array, size_t numElements, size_t size, CompareFunc compare, int isAscending) {
    char* arr = (char*)array;
    for (size_t i = 0; i < numElements - 1; i++) {
        size_t minOrMaxIdx = i;
        for (size_t j = i + 1; j < numElements; j++) {
            int cmp = compare(arr + j * size, arr + minOrMaxIdx * size);
            if ((isAscending && cmp < 0) || (!isAscending && cmp > 0)) {
                minOrMaxIdx = j;
            }
        }
        if (minOrMaxIdx != i) {
            char temp[size];
            memcpy(temp, arr + i * size, size);
            memcpy(arr + i * size, arr + minOrMaxIdx * size, size);
            memcpy(arr + minOrMaxIdx * size, temp, size);
        }
    }
}

void insertionSort(void* array, size_t numElements, size_t size, CompareFunc compare, int isAscending) {
    char* arr = (char*)array;
    for (size_t i = 1; i < numElements; i++) {
        char temp[size];
        memcpy(temp, arr + i * size, size);
        size_t j = i;
        while (j > 0) {
            int cmp = compare(temp, arr + (j - 1) * size);
            if ((isAscending && cmp < 0) || (!isAscending && cmp > 0)) {
                memcpy(arr + j * size, arr + (j - 1) * size, size);
                j--;
            } else {
                break;
            }
        }
        memcpy(arr + j * size, temp, size);
    }
}

static void merge(void* left, size_t leftSize, void* right, size_t rightSize, void* result, size_t elemSize, CompareFunc compare, int isAscending) {
    size_t i = 0, j = 0, k = 0;
    char* leftArr = (char*)left;
    char* rightArr = (char*)right;
    char* resultArr = (char*)result;

    while (i < leftSize && j < rightSize) {
        if ((isAscending && compare(leftArr + i * elemSize, rightArr + j * elemSize) <= 0) ||
            (!isAscending && compare(leftArr + i * elemSize, rightArr + j * elemSize) > 0)) {
            memcpy(resultArr + k * elemSize, leftArr + i * elemSize, elemSize);
            i++;
        } else {
            memcpy(resultArr + k * elemSize, rightArr + j * elemSize, elemSize);
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        memcpy(resultArr + k * elemSize, leftArr + i * elemSize, elemSize);
        i++;
        k++;
    }

    while (j < rightSize) {
        memcpy(resultArr + k * elemSize, rightArr + j * elemSize, elemSize);
        j++;
        k++;
    }
}

void mergeSort(void* array, size_t numElements, size_t size, CompareFunc compare, int isAscending) {
    if (numElements > 1) {
        size_t mid = numElements / 2;
        void* left = createArray(mid, size);
        void* right = createArray(numElements - mid, size);

        memcpy(left, array, mid * size);
        memcpy(right, (char*)array + mid * size, (numElements - mid) * size);

        mergeSort(left, mid, size, compare, isAscending);
        mergeSort(right, numElements - mid, size, compare, isAscending);

        merge(left, mid, right, numElements - mid, array, size, compare, isAscending);

        destroyArray(left);
        destroyArray(right);
    }
}

void printArray(const void* array, size_t numElements, size_t size, void (*printElement)(const void*)) {
    const char* arr = (const char*)array;
    for (size_t i = 0; i < numElements; i++) {
        printElement(arr + i * size);
        printf("\n");
    }
}
