import time
import random


def miller_rabin(n, k):
    if n == 2:
        return True
    if n % 2 == 0:
        return False

    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2

    for _ in range(k):
        a = random.randrange(2, n - 1)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue

        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False

    return True


num = int(input('Ingresa un número entero de hasta 20 dígitos: '))

inicio = time.time()


if miller_rabin(num, 90):
    print(f'{num} es probablemente un número primo.')
else:
    print(f'{num} es un número compuesto.')


fin = time.time()
print(fin-inicio)  # 1.0005340576171875
