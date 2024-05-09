#include "actors/TomHanks.h"
#include "actors/AndrewStanton.h"


int main() {
    TomHanks tom;
    tom.actuar();
    
    AndrewStanton andrew;
    andrew.actuar();
    
    
    delete &tom;
    delete &andrew;
    // andrew.destruir(heroe);
    return 0;
}