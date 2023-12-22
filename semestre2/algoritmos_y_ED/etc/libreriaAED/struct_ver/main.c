
#include <stdio.h>
#include <string.h>  // for strcpy

#include "sort.h"

typedef struct {
    char name[50];
    int age;
} Person;

int compareByAge(const void* a, const void* b) {
    const Person* personA = (const Person*)a;
    const Person* personB = (const Person*)b;
    return personA->age - personB->age;
}

void printPerson(const void* element) {
    const Person* person = (const Person*)element;
    printf("Name: %s, Age: %d", person->name, person->age);
}

int main() {
    // Sample data
    Person people[] = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35},
        {"Dave", 20},
        {"Eve", 28}};
    size_t numPeople = sizeof(people) / sizeof(people[0]);

    // Print original array
    printf("Original array:\n");
    printArray(people, numPeople, sizeof(Person), printPerson);
    printf("\n");

    // Selection sort
    selectionSort(people, numPeople, sizeof(Person), compareByAge, 1);  // 1 for ascending order
    printf("Array after Selection Sort (Ascending):\n");
    printArray(people, numPeople, sizeof(Person), printPerson);
    printf("\n");

    // Resetting array to original order for next sort (not shown, but assumed)

    // Insertion sort
    insertionSort(people, numPeople, sizeof(Person), compareByAge, 0);  // 0 for descending order
    printf("Array after Insertion Sort (Descending):\n");
    printArray(people, numPeople, sizeof(Person), printPerson);
    printf("\n");

    // Resetting array to original order for next sort (not shown, but assumed)

    // Merge sort
    mergeSort(people, numPeople, sizeof(Person), compareByAge, 1);  // 1 for ascending order
    printf("Array after Merge Sort (Ascending):\n");
    printArray(people, numPeople, sizeof(Person), printPerson);
    printf("\n");

    return 0;
}
