
#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

bool es_primo(mpz_t n) {
    if (mpz_cmp_ui(n, 1) <= 0) {
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0) {
        return true;
    }
    if (mpz_even_p(n)) {
        return false;
    }
    mpz_t i;
    mpz_init(i);
    mpz_set_ui(i, 3);
    mpz_t raiz;
    mpz_init(raiz);
    mpz_sqrt(raiz, n);
    while (mpz_cmp(i, raiz) <= 0) {
        if (mpz_divisible_p(n, i)) {
            mpz_clear(i);
            mpz_clear(raiz);
            return false;
        }
        mpz_add_ui(i, i, 2);
    }
    mpz_clear(i);
    mpz_clear(raiz);
    return true;
}

int main() {
    mpz_t num;
    mpz_init(num);
    gmp_printf("Ingresa un número entero de hasta 20 dígitos: ");
    gmp_scanf("%Zd", num);

    clock_t inicio = clock();

    // Código a medir
    if (es_primo(num)) {
        gmp_printf("%Zd es un número primo.\n", num);
    } else {
        gmp_printf("%Zd es un número compuesto.\n", num);
    }

    clock_t fin = clock();
    double tiempo_transcurrido = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("%f\n", tiempo_transcurrido);

    mpz_clear(num);

    return 0;
}

// Original

// #include <math.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <time.h>

// bool es_primo(unsigned long long int n) {
//     if (n <= 1) {
//         return false;
//     }
//     if (n == 2) {
//         return true;
//     }
//     if (n % 2 == 0) {
//         return false;
//     }
//     for (unsigned long long int i = 3; i <= sqrt(n); i += 2) {
//         if (n % i == 0) {
//             return false;
//         }
//     }
//     return true;
// }

// int main() {
//     unsigned long long int num;
//     printf("Ingresa un número entero de hasta 20 dígitos: ");
//     scanf("%llu", &num);

//     clock_t inicio = clock();

//     // Código a medir
//     if (es_primo(num)) {
//         printf("%llu es un número primo.\n", num);
//     } else {
//         printf("%llu es un número compuesto.\n", num);
//     }

//     clock_t fin = clock();
//     double tiempo_transcurrido = (double)(fin - inicio) / CLOCKS_PER_SEC;
//     printf("%f\n", tiempo_transcurrido);

//     return 0;
// }