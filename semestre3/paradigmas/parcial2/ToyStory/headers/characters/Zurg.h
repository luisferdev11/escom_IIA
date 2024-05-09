#ifndef ZURG_H
#define ZURG_H

#include "interfaces/Villano.h"

class Zurg : public Villano {
public:
    void destruir(Villano& miVillano) override;
    void destruir(Heroe& miHeroe) override;
    void destruir(Juguete& miJuguete) override;
    void destruir() override;
};

#endif