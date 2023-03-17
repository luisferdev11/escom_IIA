#include<stdio.h>

int suma;

int main(){
    int n1, n2, suma;
    printf("Numero 1: ");
    scanf("%d", &n1);
    
    printf("Numero 2: ");
    scanf("%d", &n2);

    suma = n1 + n2;

    printf("La suma es: %d \n", suma);

    return 0;
}