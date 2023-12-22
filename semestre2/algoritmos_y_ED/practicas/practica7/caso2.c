/*
Luis Fernando Rodriguez Dominguez
2BV2
Ingenieria en Inteligencia Artificial
1-dic-2023
*/

#include <stdio.h>
#include <stdlib.h>

// Estructura para un nodo de lista simplemente enlazada
typedef struct SNode {
    int data;
    struct SNode* next;
} SNode;

// Estructura para un nodo de lista doblemente enlazada
typedef struct DNode {
    int data;
    struct DNode* prev;
    struct DNode* next;
} DNode;

void appendDNode(DNode** head, int data) {
    DNode* new_node = (DNode*)malloc(sizeof(DNode));
    DNode* last = *head;

    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        new_node->prev = NULL;
        *head = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    new_node->prev = last;
}

DNode* mergeAndRemoveDuplicates(SNode* head1, SNode* head2) {
    DNode* result = NULL;
    SNode *ptr1 = head1, *ptr2 = head2;
    int lastAdded = -1;  // Suponiendo que los datos son siempre positivos

    while (ptr1 != NULL && ptr2 != NULL) {
        if (ptr1->data == ptr2->data) {
            if (lastAdded != ptr1->data) {
                appendDNode(&result, ptr1->data);
                lastAdded = ptr1->data;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        } else if (ptr1->data < ptr2->data) {
            if (lastAdded != ptr1->data) {
                appendDNode(&result, ptr1->data);
                lastAdded = ptr1->data;
            }
            ptr1 = ptr1->next;
        } else {
            if (lastAdded != ptr2->data) {
                appendDNode(&result, ptr2->data);
                lastAdded = ptr2->data;
            }
            ptr2 = ptr2->next;
        }
    }

    // Procesar los elementos restantes de cada lista
    while (ptr1 != NULL) {
        if (lastAdded != ptr1->data) {
            appendDNode(&result, ptr1->data);
            lastAdded = ptr1->data;
        }
        ptr1 = ptr1->next;
    }

    while (ptr2 != NULL) {
        if (lastAdded != ptr2->data) {
            appendDNode(&result, ptr2->data);
            lastAdded = ptr2->data;
        }
        ptr2 = ptr2->next;
    }

    return result;
}

SNode* createSNode(int data) {
    SNode* new_node = (SNode*)malloc(sizeof(SNode));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void printSList(SNode* head) {
    SNode* node = head;
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
    printf("\n");
}

void printDList(DNode* head) {
    DNode* node = head;
    while (node != NULL) {
        printf("%d <-> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
    printf("\n");
}

int main() {
    SNode *list1 = NULL, *list2 = NULL;

    list1 = createSNode(1);
    list1->next = createSNode(2);
    list1->next->next = createSNode(3);
    list1->next->next->next = createSNode(4);
    list1->next->next->next->next = createSNode(5);

    list2 = createSNode(2);
    list2->next = createSNode(4);
    list2->next->next = createSNode(6);
    list2->next->next->next = createSNode(8);
    list2->next->next->next->next = createSNode(10);

    printSList(list1);
    printSList(list2);

    // Mezclar las listas y eliminar duplicados
    DNode* mergedList = mergeAndRemoveDuplicates(list1, list2);

    puts("Lista mergeada y ordenada:");
    printDList(mergedList);

    free(list1);
    free(list2);
    free(mergedList);

    return 0;
}
