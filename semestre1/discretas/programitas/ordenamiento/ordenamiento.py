def minusculas(word):
    result = ''
    for char in word:
        ascii_value = ord(char)
        if 65 <= ascii_value <= 90:
            result += chr(ascii_value + 32)
        else:
            result += char
    return result


def acentos(word):
    accents = {
        'Á': 'A', 'É': 'E', 'Í': 'I', 'Ó': 'O', 'Ú': 'U', 'Ü': 'U',
        'á': 'a', 'é': 'e', 'í': 'i', 'ó': 'o', 'ú': 'u', 'ü': 'u',
        'Ñ': 'N', 'ñ': 'n'
    }
    return ''.join(accents.get(c, c) for c in word)


def compara_palabras(palabra1, palabra2):
    palabra1 = minusculas(acentos(palabra1))
    palabra2 = minusculas(acentos(palabra2))

    for i in range(min(len(palabra1), len(palabra2))):
        if ord(palabra1[i]) > ord(palabra2[i]):
            return True
        elif ord(palabra1[i]) < ord(palabra2[i]):
            return False

    return len(palabra1) >= len(palabra2)


def ordena_palabras(lista_palabras):
    for i in range(len(lista_palabras)):
        for j in range(len(lista_palabras) - i - 1):
            if not compara_palabras(lista_palabras[j], lista_palabras[j+1]):
                lista_palabras[j], lista_palabras[j +
                                                  1] = lista_palabras[j+1], lista_palabras[j]

    return lista_palabras


seleccion = int(input("Cuantas palabras quiere ingresar?: "))

palabras = []
for i in range(seleccion):
    palabra = input("Escribe tu palabra: ")
    palabras.append(palabra)

print(palabras)

lista_ordenada = ordena_palabras(palabras)
print(lista_ordenada)
