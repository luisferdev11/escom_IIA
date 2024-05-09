#ifndef VILLANO_H
#define VILLANO_H

#include "Heroe.h"
#include "Juguete.h"

class Villano {
public:
    // puede destrutir Heroe, Villano, Juguete
    virtual void destruir(Villano& miVillano) = 0;
    virtual void destruir(Heroe& miHeroe) = 0;
    virtual void destruir(Juguete& miJuguete) = 0;
    virtual void destruir() = 0;
    virtual ~Villano() {}
};

#endif 