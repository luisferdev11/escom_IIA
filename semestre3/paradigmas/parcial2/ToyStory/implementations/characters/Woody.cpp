#include "characters/Woody.h"
#include <iostream>

Woody::Woody() : Juguete("Woody") {}

void Woody::salvar() {
    std::cout << "Woody salva el día!" << std::endl;
}

void Woody::apoyar() {
    std::cout << "Woody apoya a sus amigos!" << std::endl;
}

void Woody::montar() {
    std::cout << "Woody monta a Bullseye!" << std::endl;
}

void Woody::impartirLey() {
    std::cout << "Woody imparte la ley!" << std::endl;
}   

void Woody::jugar() {
    std::cout << "Woody juega con sus amigos!" << std::endl;
}   

void Woody::arrearGanado() {
    std::cout << "Woody arrea el ganado!" << std::endl;
}

void Woody::chistar() {
    std::cout << "Woody chista!" << std::endl;
}

