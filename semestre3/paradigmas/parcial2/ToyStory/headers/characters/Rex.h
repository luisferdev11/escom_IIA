#ifndef REX_H
#define REX_H

#include "interfaces/Villano.h"
#include "interfaces/Gamer.h"
#include "interfaces/Dinosaurio.h"
#include "interfaces/Juguete.h"

class Rex : public Gamer, public Dinosaurio, public Juguete {
public:
    Rex();
    void jugarVideojuegos() override;
    void rugir() override;
    void jugar() override;
    void vencer(Villano* villano);
};

#endif