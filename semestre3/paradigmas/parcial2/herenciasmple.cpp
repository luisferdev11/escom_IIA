#include <iostream>
#include <string>

using namespace std;

class SerHumano {
private:
	string genero;
	double peso;
	double talla;
public:
	SerHumano() {
		genero = "";
		peso = 0.0;
		talla = 0.0;
	}
	SerHumano(string genero, double peso, double talla) {
		this->genero = genero;
		this->peso = peso;
		this->talla = talla;
	}
	SerHumano(SerHumano *humano) {
		genero = humano->genero;
		peso = humano->peso;
		talla = humano->talla;
	}
	~SerHumano() {
		cout << "Destruyendo SerHumano" << endl;
	}
	void setSerHumano(string genero, double peso, double talla) {
		this->genero = genero;
		this->peso = peso;
		this->talla = talla;
	}
	void respirar() {
		cout << "Respirando" << endl;
	}
	bool equals(SerHumano *humano) {
		if(humano==NULL) {
			return false;
			}
		return genero.compare(humano->genero)==0 && peso==humano->peso &&
				talla==humano->talla;
	}
	string toString() {
		return "Genero: " + genero + ".\n" +
			   "Peso  : " + to_string(peso)   + " kilos.\n" +
			   "Talla : " + to_string(talla)  + " centimetros.\n";
	}
};

class Persona : public SerHumano {
private:
	string nombre;
	int edad;
public:
	Persona() : SerHumano() {
		nombre = "";
		edad = 0;
	}
	Persona(string genero, double peso, double talla,
		string nombre, int edad) : SerHumano(genero, peso, talla) {
		this->nombre = nombre;
		this->edad = edad;
	}
	Persona(Persona *alguien) : SerHumano(alguien) {
		nombre = alguien->nombre;
		edad = alguien->edad;
	}
	~Persona() {
		cout << "Destruyendo Persona" << endl;
	}
	void setPersona(string genero, double peso, double talla,
		string nombre, int edad) {
		setSerHumano(genero, peso, talla);
		this->nombre = nombre;
		this->edad = edad;
	}
	void respirar(string estado) {
		SerHumano::respirar();
		if(estado.compare("Agitado")==0) {
			cout << "agh, agh, agh" << endl;
			}
		else
		if(estado.compare("Nervioso")==0) {
			cout << "agh, agh, agh, agh, agh, agh" << endl;
			}
		else
		if(estado.compare("Tranquilo")==0) {
			cout << " .... " << endl;
			}
	}
	void comer() {
		cout << "nam, nam, nam" << endl;
	}
	bool equals(Persona *persona) {
		if(persona==NULL) {
			return false;
		}
		return SerHumano::equals(persona) && 
				nombre.compare(persona->nombre)==0 &&
				edad==persona->edad;
	}
	string toString() {
		return SerHumano::toString() + 
				"Nombre: " + nombre + "\n" +
				"Edad  : " + to_string(edad) + "\n";
	}
};

int main(int argc, char *argv[]) {
	Persona *luisa = new Persona("Femenino", 3.6, 40.5, 
		"Luisa Perez Dominguez", 15);
	cout << luisa->toString();
	luisa->SerHumano::respirar();
	luisa->respirar("Tranquilo");
	luisa->comer();

	Persona *copiaLuisa = new Persona(luisa);
	cout << copiaLuisa->toString();
	copiaLuisa->SerHumano::respirar();
	copiaLuisa->respirar("Tranquilo");
	copiaLuisa->comer();

	cout << copiaLuisa->equals(luisa) << endl;

	delete luisa;
	delete copiaLuisa;
	return 0;
}