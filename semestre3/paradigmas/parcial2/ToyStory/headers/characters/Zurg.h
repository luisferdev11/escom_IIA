#ifndef ZURG_H
#define ZURG_H

#include "interfaces/Villano.h"

class Zurg : public Villano, public Juguete {
public:
    Zurg();
    void destruir(Villano* miVillano) override;
    void destruir(Heroe* miHeroe) override;
    void destruir(Juguete* miJuguete) override;
    void destruir() override;
    void jugar() override;

    virtual void decirLaVerdad();
    virtual void disparar();
};

#endif