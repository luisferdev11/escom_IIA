#ifndef SORT_H
#define SORT_H

#include <stddef.h>  // for size_t

// Comparison function type
typedef int (*CompareFunc)(const void*, const void*);

// Function declarations

void* createArray(size_t numElements, size_t size);
void destroyArray(void* array);
void selectionSort(void* array, size_t numElements, size_t size, CompareFunc compare, int isAscending);
void insertionSort(void* array, size_t numElements, size_t size, CompareFunc compare, int isAscending);
void mergeSort(void* array, size_t numElements, size_t size, CompareFunc compare, int isAscending);      // Modified divide function
void printArray(const void* array, size_t numElements, size_t size, void (*printElement)(const void*));  // For printing elements

#endif  // SORT_H