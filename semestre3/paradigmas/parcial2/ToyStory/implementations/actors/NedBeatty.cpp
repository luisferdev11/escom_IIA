#include "actors/NedBeatty.h"
#include <iostream>

NedBeatty::NedBeatty() : Actor("Ned Beatty") {}

void NedBeatty::actuar() {
    std::cout << name << " está actuando como Lotso." << std::endl;
    abrazar();
    comerMiel();
    olerRico();
    mentir();
    destruir();
}
