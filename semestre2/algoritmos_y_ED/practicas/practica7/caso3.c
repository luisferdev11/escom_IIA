/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
1-dic-2023
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;  // Puede ser int o char
    struct Node* next;
} Node;

void append(Node** head, char data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;

    if (*head == NULL) {
        new_node->next = new_node;
        *head = new_node;
        return;
    }

    Node* last = *head;
    while (last->next != *head) {
        last = last->next;
    }

    last->next = new_node;
    new_node->next = *head;
}

Node* reverse(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

// Función para obtener el tamaño de la lista circular
int getSize(Node* head) {
    if (head == NULL) return 0;
    int size = 1;
    Node* current = head->next;
    while (current != head) {
        size++;
        current = current->next;
    }
    return size;
}

// Función para avanzar un nodo en la lista circular, con control de envoltura
Node* advance(Node* current, int size) {
    while (size--) {
        current = current->next;
    }
    return current;
}

// Función para verificar si la lista es palíndromo
int isPalindrome(Node* head) {
    int size = getSize(head);
    Node* start = head;
    Node* end = head;

    // Avanzar el puntero 'end' al último nodo
    end = advance(end, size - 1);

    for (int i = 0; i < size / 2; i++) {
        if (start->data != end->data) {
            return 0;
        }
        start = start->next;
        end = advance(head, size - 2 - i);
    }
    return 1;
}

int main() {
    Node* head = NULL;

    // Crear la lista circular
    append(&head, 'a');
    append(&head, 'b');
    append(&head, 'c');
    append(&head, 'c');
    append(&head, 'b');
    append(&head, 'a');

    printf("Lista: ");
    Node* node = head;
    while (node->next != head) {
        printf("%c ", node->data);
        node = node->next;
    }

    printf("%c\n", node->data);

    if (isPalindrome(head))
        printf("Es palíndromo\n");
    else
        printf("No es palíndromo\n");

    // Liberar la memoria de la lista
    Node* current = head;

    while (current->next != head) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    free(current);

    return 0;
}
