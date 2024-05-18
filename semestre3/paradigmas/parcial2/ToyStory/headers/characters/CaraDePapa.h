#ifndef CARADEPAPA_H
#define CARADEPAPA_H

#include "interfaces/Juguete.h"
#include "interfaces/Papa.h"
#include "interfaces/Tortilla.h"
#include "interfaces/Pepino.h"

class CaraDePapa : public Juguete, public Papa, public Tortilla, public Pepino {
public:
    CaraDePapa();
    void jugar() override;
    void romper() override;
    void marchitar() override;
    void crecer() override;

    void desarmar();
};
    
#endif 