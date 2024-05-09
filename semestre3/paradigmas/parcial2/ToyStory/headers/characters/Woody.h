#ifndef WOODY_H
#define WOODY_H

#include "interfaces/Heroe.h"
#include "interfaces/AmigoFiel.h"
#include "interfaces/Jinete.h"
#include "interfaces/Sheriff.h"
#include "interfaces/Juguete.h"
#include "interfaces/Vaquero.h"

class Woody : public Heroe, public AmigoFiel, public Jinete, public Sheriff, public Juguete, public Vaquero {
public:
    void salvar() override;
    void apoyar() override;
    void montar() override;
    void impartirLey() override;
    void jugar() override;
    void arrearGanado() override;
    void chistar();
};

#endif // WOODY_H
