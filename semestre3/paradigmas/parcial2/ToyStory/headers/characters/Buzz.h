#ifndef BUZZ_H
#define BUZZ_H

#include "interfaces/Juguete.h"
#include "interfaces/Heroe.h"
#include "interfaces/Astronauta.h"
#include "Zurg.h"

class Buzz : public Heroe, public Astronauta, public Zurg {
public:
    // std::string nombre;
    // Buzz();
    // Buzz(const std::string& n);
    void jugar() override;
    void salvar() override;
    void viajarAlEspacio() override;
    void destruir(Villano* miVillano) override;
    void destruir(Heroe* miHeroe) override;
    void destruir(Juguete* miJuguete) override;
    void destruir() override;
    void decirLaVerdad() override;
    void disparar() override;

    void caerConEstilo();
    void dispararLaser();
};

#endif
