class Pelota:
    def __init__(self, alto, ancho, color):
        self.alto = alto
        self.ancho = ancho
        self.color = color

def crearPelota(pelotas):
    alto = int(input("Alto: "))
    ancho = int(input("Ancho: "))
    color = input("Color: ")
    nueva_pelota = Pelota(alto, ancho, color)
    pelotas.append(nueva_pelota)

def destruirPelota(pelotas):
    indice = int(input("Índice de la pelota a destruir: ")) - 1
    if indice < 0 or indice >= len(pelotas):
        print("Índice no válido.")
        return
    del pelotas[indice]

def leerPelotas(pelotas):
    for i, pelota in enumerate(pelotas):
        print(f"Pelota {i+1}:")
        print(f"Alto: {pelota.alto}")
        print(f"Ancho: {pelota.ancho}")
        print(f"Color: {pelota.color}")

def menuOperaciones():
    pelotas = []
    while True:
        print("1. Crear pelota")
        print("2. Destruir pelota")
        print("3. Leer pelotas")
        print("4. Salir")
        opcion = int(input("Opción: "))
        
        if opcion == 1:
            crearPelota(pelotas)
        elif opcion == 2:
            destruirPelota(pelotas)
        elif opcion == 3:
            leerPelotas(pelotas)
        elif opcion == 4:
            print("Saliendo...")
            break
        else:
            print("Opción inválida.")

if __name__ == "__main__":
    menuOperaciones()
