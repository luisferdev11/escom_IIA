#ifndef LOTSO_H
#define LOTSO_H

#include "interfaces/Peluche.h"
#include "interfaces/Villano.h"
#include "interfaces/Oso.h"

class Lotso : public Peluche, public Villano, public Oso {
public:
    // Lotso();
    void abrazar() override;
    void olerRico() override;
    void destruir(Villano* miVillano) override;
    void destruir(Heroe* miHeroe) override;
    void destruir(Juguete* miJuguete) override;
    void destruir() override;
    void comerMiel() override;
    void mentir();
};

#endif