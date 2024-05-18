#include "actors/TimAllen.h"
#include <iostream>

TimAllen::TimAllen() : Actor("Tim Allen") {}

void TimAllen::actuar() {
    std::cout << name << " está actuando como Buzz." << std::endl;
    jugar();
    salvar();
    viajarAlEspacio();
    destruir();
    decirLaVerdad();
    disparar();
    caerConEstilo();
    dispararLaser();
}