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


try:
    # Solicitar al usuario los valores del dividendo y divisor
    dividendo = int(input("Ingrese el dividendo: "))
    divisor = int(input("Ingrese el divisor: "))

    # Llamar a la función y obtener el cociente y residuo
    cociente, residuo = division(dividendo, divisor)
    print(f"{dividendo} = {divisor} * {cociente} + {residuo}")
except:
    print("Esto no se puede hacer >:l")
