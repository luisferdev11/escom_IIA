from numba import cuda
import math


@cuda.jit
def es_primo_cuda(n, result):
    idx = cuda.grid(1)
    if idx < 2 or idx > int(math.sqrt(n)):
        return
    if n % idx == 0:
        result[0] = False


def es_primo(n):
    result = cuda.to_device([True])
    block_size = 128
    grid_size = (n + block_size - 1) // block_size
    es_primo_cuda[grid_size, block_size](n, result)
    return result.copy_to_host()[0]


num = int(input('Ingresa un número entero de hasta 20 dígitos: '))
if es_primo(num):
    print(f'{num} es un número primo.')
else:
    print(f'{num} es un número compuesto.')
