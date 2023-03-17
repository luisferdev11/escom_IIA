class Set:
    def __init__(self, initial_values=None):
        self.set = []
        if initial_values:
            for value in initial_values:
                self.add(value)

    def add(self, value):
        if value not in self.set:
            self.set.append(value)

    def remove(self, value):
        if value in self.set:
            self.set.remove(value)

    def size(self):
        return len(self.set)

    def union(self, other_set):
        new_set = Set(self.set)  # [] copia del conjunto original
        for value in other_set.set:     # Está en el otro set (B)
            # No está en el set original (A), lo agregamos
            if value not in self.set:
                new_set.add(value)
        return new_set

    def intersection(self, other_set):
        new_set = Set()
        for value in self.set:
            if value in other_set.set:
                new_set.add(value)
        return new_set

    def difference(self, other_set):
        new_set = Set(self.set)
        for value in other_set.set:
            if value in self.set:
                new_set.remove(value)
        return new_set

    def complement(self, universal_set):
        new_set = Set()
        for element in universal_set.set:
            if element not in self.set:
                new_set.add(element)
        return new_set

    def calc_powerset(self, seq):
        if len(seq) == 0:
            yield seq
        if len(seq) == 1:
            yield seq
            yield []
        elif len(seq) > 1:
            for item in self.calc_powerset(seq[1:]):
                yield [seq[0]]+item
                yield item

    def get_powerset(self):
        my_powerset = Set()

        for element in self.calc_powerset(self.set):
            my_powerset.add(element)

        return my_powerset


def createUniverse(a):  # a es el primer argumento del programita
    conjunto = []
    for element in range(-a, a+1):
        conjunto.append(element)
    return conjunto


def getOddUniverse(U):
    return [oddElement for oddElement in U if oddElement % 2 == 1]


def createSetB(c):
    conjunto = []
    for element in range(c):
        conjunto.append(element + 1)
    return conjunto


def createSetC(U, d):
    if d == 0:
        return []
    return [element for element in U if element % d == 0]


"""
Primera operacion
"""


def task1(A, B, C, U):
    izquierda = A.union(B).complement(U)  # (AUB)c

    derecha = A.union(C).complement(U)  # (AUC)c

    # print(izquierda.set)
    # print(derecha.set)

    total = izquierda.intersection(derecha)
    return total


"""
Segunda operacion
"""


def task2(A, B, C, U):
    total = A.intersection(B).intersection(C).complement(U)
    return total

# print(f"Segunda: {task2(A, B, C, U)}")


"""
Tercera operacion
"""


def task3(A, B, C, U):
    izquierda = A.intersection(B).complement(U)

    derecha = A.intersection(C).complement(U)
    total3 = izquierda.union(derecha)

    return total3


if __name__ == "__main__":
    go = True
    while go:
        print("Hola cñor Darwin vamos a calcular algunas operaciones con conjuntos")

        while True:
            try:
                a = int(
                    input("Ingresa a, este tiene que ser entero y va a generar nuestro universo: "))
                if a < 0:
                    a = a*-1

                U = Set(createUniverse(a))
                A = Set(getOddUniverse(U.set))

                break
            except:
                print("Eso no es un entero, ingresa un entero")

        while True:

            if a == 0:
                print("No te pedimos c porque B tiene que ser el vacío")
                B = Set()
                break
            try:
                c = int(input(
                    "Ingresa c, este tiene que ser entero positivo y menor al numero que has ingresado previamente, nos creará un conjunto de 1 a c: "))
                if c > a:
                    print(
                        "El número debe ser menor o igual al parametro a para que siga definido dentro del universo")
                elif c <= 0:
                    print("Tiene que ser mayor a 0")
                else:
                    B = Set(createSetB(c))
                    break
            except:
                print("Eso no es entero positivo")

        while True:
            try:
                d = int(input(
                    "Ingresa d, este tiene que ser entero y va a dividir a nuestro conjunto B: "))
                C = Set(createSetC(U.set, d))
                break
            except:
                print("Ingresa un entero")

        print(f"U: {U.set}")
        print(f"A: {A.set}")
        print(f"B: {B.set}")
        print(f"C: {C.set}")

        first_task = task1(A, B, C, U)
        second_task = task2(A, B, C, U)
        third_task = task3(A, B, C, U)

        print(f"(AUB)c n (AUC)c: {first_task.set}")
        print(f"(AnBnC)c: {second_task.set}")
        print(f"(AnB)c U (AnC)c: {third_task.set}")

        Upotencia = U.get_powerset()
        print(f"Potencia de U: {Upotencia.set}")

        power1 = first_task.get_powerset()
        power2 = second_task.get_powerset()
        power3 = third_task.get_powerset()

        print(f"Potencia de (AUB)c n (AUC)c: {power1.set}")
        print(f"Potencia de (AnBnC)c: {power2.set}")
        print(f"Potencia de (AnB)c U (AnC)c: {power3.set}")

        print(f"Cardialidad de (AUB)c n (AUC)c: {len(power1.set)}")
        print(f"Cardialidad de (AnBnC)c: {len(power2.set)}")
        print(f"Cardialidad de (AnB)c U (AnC)c: {len(power3.set)}")

        again = input(
            "Presione 1 para volver a ejecutar o cualquier otro digito para cerrar: ")

        if again != "1":
            go = False
