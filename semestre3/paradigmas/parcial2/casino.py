import random


class Dado:
    NUMERO_CARAS = 6
    caraSuperior = 1

    def __init__(self):
        NUMERO_CARAS = 6
        caraSuperior = 1

    def mostrarCaraSuperior(self):
        print(self.caraSuperior)

    def caerEnCaraSuperior(self):
        self.caraSuperior = random.randint(1, self.NUMERO_CARAS)
        self.mostrarCaraSuperior()
        return self.caraSuperior


class Jugador:
    numero = 7
    dadoUno = Dado()
    dadoDos = Dado()

    def __init__(self):
        numero = 7
        dadoUno = Dado()
        dadoDos = Dado()

    def tomarLosDados(self, dadoUno, dadoDos):
        self.dadoUno = dadoUno
        self.dadoDos = dadoDos

    def agitarLosDados(self):
        print("clack clack clack")

    def soplarLosDados(self):
        print("shhhhhhhhhhhhhhhhh")

    def ponerSuNumero(self, numero):
        self.numero = numero

    def lanzarLosDados(self):
        return self.dadoUno.caerEnCaraSuperior() + self.dadoDos.caerEnCaraSuperior()

    def tomarSuNumero(self):
        return self.numero


class JuegoDeDado:
    dadoUno = Dado()
    dadoDos = Dado()
    player = Jugador()

    def __init__(self):
        dadoUno = Dado()
        dadoDos = Dado()
        player = Jugador()

    def jugarElJuego(self, numero):
        self.player.tomarLosDados(self.dadoUno, self.dadoDos)
        self.player.agitarLosDados()
        self.player.soplarLosDados()
        self.player.ponerSuNumero(numero)
        numeroGanador = self.player.lanzarLosDados()
        if numeroGanador == self.player.tomarSuNumero():
            print("GANASTE con ", numeroGanador)
        else:
            print("PERDISTE porque ", numeroGanador, " es diferente de ", self.player.tomarSuNumero())



juego = JuegoDeDado()
juego.jugarElJuego(7)
#juego.dadoUno.NUMERO_CARAS = 12
#juego.jugarElJuego(8)