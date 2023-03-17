#include <stdio.h>

int main()
{
    int numero1, numero2;
    int auxiliar;

    printf("Primera variable: ");
    scanf("%d", &numero1);

    printf("Segunda varible: ");
    scanf("%d", &numero2);

    auxiliar = numero1;
    numero1 = numero2;
    numero2 = auxiliar;

    printf("Ahora el primer numero es: %d \n", numero1);
    printf("Ahora el segundo numero es: %d \n", numero2);
    return 0;
}
