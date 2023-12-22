/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
1-dic-2023
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
} DoublyLinkedList;

void append(DoublyLinkedList* list, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;

    if (list->head == NULL) {
        new_node->prev = NULL;
        list->head = new_node;
        return;
    }

    Node* last = list->head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;
}

void printList(DoublyLinkedList* list) {
    Node* node = list->head;
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL");
    printf("\n");
}

void reverse(DoublyLinkedList* list) {
    Node* temp = NULL;
    Node* current = list->head;

    // Intercambiar los punteros next y prev para cada nodo
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    // Cambiar el head si la lista no estaba vacía
    if (temp != NULL) {
        list->head = temp->prev;
    }
}

int main() {
    DoublyLinkedList list = {NULL};

    append(&list, 1);
    append(&list, 2);
    append(&list, 3);
    append(&list, 4);

    printf("Lista original:\n");
    printList(&list);

    reverse(&list);

    printf("Lista invertida:\n");
    for (Node* node = list.head; node != NULL; node = node->next) {
        printf("%d, ", node->data);
    }
    printf("\n");

    return 0;
}
