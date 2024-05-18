#include "characters/Zurg.h"
#include <iostream>

Zurg::Zurg() : Juguete("Zurg") {}

void Zurg::destruir(Villano* miVillano) {
    std::cout << "Zurg destruye a otro villano" << std::endl;
}

void Zurg::destruir(Heroe* miHeroe) {
    std::cout << "Zurg destruye a un héroe" << std::endl;
}

void Zurg::destruir(Juguete* miJuguete) {
    std::cout << "Zurg destruye a un juguete" << std::endl;
}

void Zurg::destruir() {
    std::cout << "Zurg destruye a alguien" << std::endl;
}

void Zurg::jugar() {
    std::cout << "Zurg está jugando" << std::endl;
}

void Zurg::decirLaVerdad() {
    std::cout << "Yo soy tu padre, ha dicho Zurg" << std::endl;
}

void Zurg::disparar() {
    std::cout << "Zurg dispara. Pium, pium" << std::endl;
}