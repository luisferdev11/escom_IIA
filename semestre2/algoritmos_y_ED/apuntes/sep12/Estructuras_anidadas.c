/* Estructuras y Uniones */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// abstraer es la extraccion de las caracteristicas generales de un objeto
typedef struct {
    char marca[40];
} Calzado;

typedef struct {
    float altura;        // 4 bytes
    float peso;          // 4 bytes
    char colorPiel[30];  // 30 bytes
    int edad;            // 4 bytes
    Calzado zapatos;
} Persona;  // 42 bytes

// int main(int argc, char const* argv[]) {
//     // Persona jacinto = {1.70, 55.5, "blanca", 28};

//     Persona jacinto;
//     Persona* pJacinto = &jacinto;

//     pJacinto->edad = 50;
//     printf("La edad de la persona es: %d\n", pJacinto->edad);

//     pJacinto->edad = 34;

//     printf("La nueva edad de la persona es: %d\n", jacinto.edad);
//     return 0;
// }

// Arreglo dinamico
int main(int argc, char const* argv[]) {
    // Persona jacinto = {1.70, 55.5, "blanca", 28};

    Persona jacinto;
    Persona* p = calloc(10, sizeof(Persona));

    p[5].edad = 25;

    printf("La edad de la persona es: %d\n", (p + 5)->edad);

    // printf("La nueva edad de la persona es: %d\n", jacinto.edad);

    free(p);
    return 0;
}