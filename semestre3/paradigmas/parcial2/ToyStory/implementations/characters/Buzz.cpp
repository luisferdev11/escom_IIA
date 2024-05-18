#include "characters/Buzz.h"
#include <iostream>

// No podemos usar Juguete::Juguete() porque Juguete hereda a Zurg y Zurg no tiene constructor por defecto

// Buzz::Buzz(const std::string& n) : nombre(n) {}

void Buzz::jugar() {
    std::cout << "Buzz juega con Woody" << std::endl;
}

void Buzz::salvar() {
    std::cout << "Buzz salva a Woody" << std::endl;
}

void Buzz::viajarAlEspacio() {
    std::cout << "Buzz viaja al espacio" << std::endl;
}

void Buzz::destruir() {
    std::cout << "Buzz destruye a Zurg" << std::endl;
}
void Buzz::destruir(Villano* miVillano) {
    std::cout << "Buzz destruye a otro villano" << std::endl;
}

void Buzz::destruir(Heroe* miHeroe) {
    std::cout << "Buzz destruye a un héroe" << std::endl;
}

void Buzz::destruir(Juguete* miJuguete) {
    std::cout << "Buzz destruye a un juguete" << std::endl;
}

void Buzz::decirLaVerdad() {
    std::cout << "Buzz dice la verdad, anda basado" << std::endl;
}

void Buzz::disparar() {
    std::cout << "Buzz dispara" << std::endl;
}


void Buzz::caerConEstilo() {
    std::cout << "Buzz cae con estilo" << std::endl;
}

void Buzz::dispararLaser() {
    std::cout << "Buzz dispara su láser" << std::endl;
}