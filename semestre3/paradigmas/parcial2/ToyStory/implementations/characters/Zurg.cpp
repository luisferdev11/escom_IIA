#include "characters/Zurg.h"
#include <iostream>

void Zurg::destruir(Villano& miVillano) {
    std::cout << "Zurg destruye a otro villano" << std::endl;
}

void Zurg::destruir(Heroe& miHeroe) {
    std::cout << "Zurg destruye a un héroe" << std::endl;
}

void Zurg::destruir(Juguete& miJuguete) {
    std::cout << "Zurg destruye a un juguete" << std::endl;
}

void Zurg::destruir() {
    std::cout << "Zurg destruye a alguien" << std::endl;
}