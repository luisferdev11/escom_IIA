#include <stdio.h>

void print_spaces(int count) {
    if (count > 0) {
        printf(" ");
        print_spaces(count - 1);
    }
}

void print_line(int spaces, int stars) {
    if (stars == 1) {
        print_spaces(spaces);
        printf("*\n");  // Imprime una estrella y un salto de línea
    } else if (stars > 1) {
        print_spaces(spaces);
        printf("*");
        print_spaces(2 * stars - 3);  // Calcula el espacio entre estrellas
        printf("*\n");
    }
}

void print_upper_part(int size, int current) {
    if (current <= size / 2) {
        print_line(size / 2 - current, current + 1);  // Ajuste de espacios y número de estrellas
        print_upper_part(size, current + 1);
    }
}

void print_lower_part(int size, int current) {
    if (current >= 1) {
        print_line(size / 2 - current + 1, current);  // Ajuste de espacios y número de estrellas
        print_lower_part(size, current - 1);
    }
}

void print_diamond(int size) {
    print_upper_part(size, 0);
    print_lower_part(size - 1, size / 2);
}

int main() {
    int size;
    printf("Ingrese el tamaño del rombo (número impar): ");
    scanf("%d", &size);
    print_diamond(size);
    return 0;
}
