/*
Pseudocódigo:

entrada: entero hrs, real sueldo_hra
salida: real sueldo_neto

imprimir "Escribe el sueldo por hora: "
leer sueldo_hra

imprimir "Escribe el número de horas trabajadas: "
leer hrs

si hrs < 40 entonces
    sueldo_neto = (sueldo_hra * hrs) * .9;
sino
     sueldo_neto = (((sueldo_hra * (hrs-39)) * 1.5) + (sueldo_hra * 39)) * 0.9;

imprimir sueldo_neto

*/


#include <stdio.h>

int main()
{
    int hrs;
    float sueldo_neto, sueldo_hra;

    printf("Escribe el sueldo por hora: ");
    scanf("%f", &sueldo_hra);

    printf("Escribe el número de horas trabajadas: ");
    scanf("%d", &hrs);
    

    if (hrs < 40)
    {
        sueldo_neto = (sueldo_hra * hrs) * .9;
    }if (hrs >= 40)
    {
        sueldo_neto = (((sueldo_hra * (hrs-39)) * 1.5) + (sueldo_hra * 39)) * 0.9;
    }

    printf("El sueldo a pagar es de: %f \n", sueldo_neto);
    
    
    return 0;
}
