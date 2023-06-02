import time
import math


def es_primo(n):
    if n <= 1:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            print(f"Es divisor de {i}")
            return False
    return True


num = int(input('Ingresa un número entero de hasta 20 dígitos: '))

inicio = time.time()

# Código a medir

if es_primo(num):
    print(f'{num} es un número primo.')
else:
    print(f'{num} es un número compuesto.')

fin = time.time()
print(fin-inicio)
