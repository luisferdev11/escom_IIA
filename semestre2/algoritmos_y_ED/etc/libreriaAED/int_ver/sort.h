#ifndef SORT_H
#define SORT_H

int* createArray(int size);
void destroyArray(int* array);
void selectionSort(int* array, int size, int isAscending);
void divide(int* array, int size, int isAscending);                                                           // Updated for merge sort
void merge(int* leftArray, int leftSize, int* rightArray, int rightSize, int* mergedArray, int isAscending);  // Updated for merge sort
void insertionSort(int* array, int size, int isAscending);
void printArray(const int* array, int size);

#endif  // SORT_H
