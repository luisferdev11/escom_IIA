#include "actors/TomHanks.h"

#include <iostream>

TomHanks::TomHanks() : Actor("Tom Hanks") {}

void TomHanks::actuar() {
    std::cout << name << " está actuando como Woody." << std::endl;
    salvar();
    apoyar();
    montar();
    impartirLey();
    jugar();
    arrearGanado();
    chistar();
}