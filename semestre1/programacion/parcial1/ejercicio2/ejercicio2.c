#include <stdio.h>

int main(){
    int numero1, numero2;
    int cociente, residuo;

    printf("Vamos a obtener el cociente y residuo a partir de dos numeros\n");
    printf("Escribe el primer número: ");
    
    scanf("%d", &numero1);

    printf("Escribe el segundo número: ");
    scanf("%d", &numero2);

    cociente = numero1/numero2;

    residuo = numero1%numero2;

    printf("Cociente: %d \n", cociente);
    printf("Residuo: %d \n", residuo);

    return 0;
}