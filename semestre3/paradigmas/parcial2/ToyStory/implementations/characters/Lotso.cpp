#include "characters/Lotso.h"
#include <iostream>


void Lotso::abrazar() {
    std::cout << "Abrazando" << std::endl;
}

void Lotso::olerRico() {
    std::cout << "Oliendo rico" << std::endl;
}

void Lotso::destruir(Villano* miVillano) {
    std::cout << "Lotso destruye a otro villano" << std::endl;
}

void Lotso::destruir(Heroe* miHeroe) {
    std::cout << "Lotso destruye a un héroe" << std::endl;
}

void Lotso::destruir(Juguete* miJuguete) {
    std::cout << "Lotso destruye a un juguete" << std::endl;
}

void Lotso::destruir() {
    std::cout << "Destruyendo" << std::endl;
}

void Lotso::comerMiel() {
    std::cout << "Comiendo miel" << std::endl;
}

void Lotso::mentir() {
    std::cout << "Mintiendo" << std::endl;
}

