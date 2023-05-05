#include <gmp.h>
#include <stdio.h>

int main() {
    mpz_t n;
    mpz_init(n);
    printf("Ingresa un número entero: ");
    gmp_scanf("%Zd", n);
    if (mpz_probab_prime_p(n, 25)) {
        gmp_printf("%Zd es un número primo.\n", n);
    } else {
        gmp_printf("%Zd es un número compuesto.\n", n);
    }
    mpz_clear(n);
    return 0;
}