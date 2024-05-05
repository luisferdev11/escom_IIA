#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Dado {
private:
	int NUMERO_CARAS = 6;
	int caraSuperior;
	void mostrarCaraSuperior() {
		cout << caraSuperior << endl;
	}
public:
	Dado() {
		NUMERO_CARAS = 6;
		caraSuperior = 0;
	}
	Dado(int numeroCaras) {
		NUMERO_CARAS = numeroCaras;
		caraSuperior = 0;
	}
	~Dado() {
		cout << "Nada que destruir en Dado" << endl; 
	}
	int caerEnCaraSuperior() {
		caraSuperior = rand() % NUMERO_CARAS + 1;
		mostrarCaraSuperior();
		return caraSuperior;
	}
};

class Jugador {
private:
	int miNumero;
	Dado *dadoUno;
	Dado *dadoDos;
public:
	Jugador() {
		dadoUno = NULL;
		dadoDos = NULL;
		miNumero = 6;
	}
	~Jugador() {
		cout << "Destruyendo jugador" << endl;
		if(dadoUno!=NULL) {
			delete dadoUno;
			}
		if(dadoDos!=NULL) {
			delete dadoDos;
			}
	}
	void tomarLosDados(Dado *dadoUno, Dado *dadoDos) {
		this->dadoUno = dadoUno;
		this->dadoDos = dadoDos;
	}
	void agitarLosDados() {
		cout << "chaca, chaca" << endl;
	}
	void soplarLosDados() {
		cout << "ffffff, fffff" << endl;
	}
	void tomarMiNumero(int numero) {
		miNumero = numero;
	}
	int lanzarLosDados() {
		return dadoUno->caerEnCaraSuperior() +
				dadoDos->caerEnCaraSuperior();
	}
	int getMiNumero() {
		return miNumero;
	}
};

class JuegoDeDado {
private:
	Jugador *jugador;
	Dado *dadoUno;
	Dado *dadoDos;
public:
	JuegoDeDado() {
		jugador = new Jugador();
		dadoUno = new Dado();
		dadoDos = new Dado();
	}
	JuegoDeDado(int numeroCaras) {
		jugador = new Jugador();
		dadoUno = new Dado(numeroCaras);
		dadoDos = new Dado(numeroCaras);
	}
	~JuegoDeDado() {
		cout << "Destruyendo juego de dado" << endl;
		if(jugador!=NULL) {
			delete jugador;
			}
		if(dadoUno!=NULL) {
			delete dadoUno;
			}
		if(dadoDos!=NULL) {
			delete dadoDos;
			}
	}
	void jugarElJuego(int numero) {
		//jugador = new Jugador();
		//dadoUno = new Dado();
		//dadoDos = new Dado();
		jugador->tomarLosDados(dadoUno, dadoDos);
		jugador->agitarLosDados();
		jugador->soplarLosDados();
		jugador->tomarMiNumero(numero);
		int numeroGanador = jugador->lanzarLosDados();
		if(numeroGanador==jugador->getMiNumero()) {
			cout << "GANASTE con " << numeroGanador << endl;
			}
		else {
			cout << "PERDISTE porque " << numeroGanador << 
			" es distinto de " << jugador->getMiNumero() << endl;
			} 
	}
};

int main(int argc, char *argv[]) {
	srand(time(NULL));
	int numero;
	cout << "Introduzca un numero entre 2 y 12: ";
	cin >> numero;
	JuegoDeDado *juego = new JuegoDeDado();
	juego->jugarElJuego(numero);

	cout << "Introduzca un numero entre 2 y 24: ";
	cin >> numero;
	JuegoDeDado *otroJuego = new JuegoDeDado(12);
	otroJuego->jugarElJuego(numero);

	delete juego;
	delete otroJuego;
	return 0;
}

