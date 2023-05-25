def division(dividendo, divisor):
    # Controlar la division por cero
    if divisor == 0:
        return "Error: División por cero"

    # Manejo de signos negativos
    signo = -1 if (dividendo < 0) ^ (divisor < 0) else 1

    dividendo, divisor = abs(dividendo), abs(divisor)

    cociente = 0
    while dividendo >= divisor:
        dividendo -= divisor
        cociente += 1

    # Ajustando el cociente y el residuo si el dividendo original era negativo
    if signo == -1 and dividendo > 0:
        cociente += 1
        dividendo = divisor - dividendo

    cociente *= signo

    # El residuo siempre es positivo
    residuo = dividendo

    return cociente, residuo


def mcd_bezout(a, b):
    # Caso base
    if a == 0:
        return (b, 0, 1)
    else:
        # Llamada recursiva
        cociente, residuo = division(b, a)
        mcd, x, y = mcd_bezout(residuo, a)
        return (mcd, y - cociente * x, x)


try:
    # Solicitar al usuario los valores del dividendo y divisor
    a = int(input("Ingrese a: "))
    b = int(input("Ingrese b: "))

    if a == 0 and b == 0:
        print("El mcd está indefinido y no hay coeficientes de bezout")
    elif a == 0 or b == 0:
        if a > 0:
            mcd, x, y = mcd_bezout(a, b)
            print(f"El MCD de {a} y {b} es {mcd}.")
            print(f"La identidad de Bezout: {a}*{x} + {b}*{y} = {mcd}")
        elif b > 0:
            mcd, x, y = mcd_bezout(b, a)
            print(f"El MCD de {a} y {b} es {mcd}.")
            print(f"La identidad de Bezout: {a}*{x} + {b}*{y} = {mcd}")
    else:
        mcd, x, y = mcd_bezout(a, b)
        print(f"El MCD de {a} y {b} es {mcd}.")
        print(f"La identidad de Bezout: {a}*{x} + {b}*{y} = {mcd}")
except:
    print("Esto no se puede hacer >:l")
