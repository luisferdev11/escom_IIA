#include "actors/TomHanks.h"
#include "actors/AndrewStanton.h"
#include "actors/NedBeatty.h"
#include "actors/TimAllen.h"
#include "characters/Woody.h"
#include "characters/Rex.h"
#include "characters/CaraDePapa.h"

int main() {
    TomHanks tom;
    tom.actuar();
    
    AndrewStanton andrew;
    andrew.actuar();
    
    NedBeatty nedB;
    nedB.actuar();

    TimAllen tim;
    tim.actuar();
    
    // Crear a woody
    Woody woody;
    woody.impartirLey();

    Rex rex;
    rex.jugar();
    rex.jugarVideojuegos();
    rex.rugir();
    rex.vencer(&nedB);

    CaraDePapa caraDePapa;
    caraDePapa.jugar();
    caraDePapa.crecer();
    caraDePapa.desarmar();
    caraDePapa.marchitar();
    caraDePapa.romper();

    // delete &tom;
    // delete &andrew;
    // delete &nedB;
    // delete &tim;
    // andrew.destruir(heroe);
    return 0;
}