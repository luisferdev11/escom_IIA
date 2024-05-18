#ifndef JUGUETE_H
#define JUGUETE_H

#include <string>

class Juguete {
public:
    std::string nombre;
    Juguete(const std::string& n) : nombre(n) {}
    virtual void jugar() = 0;
    virtual ~Juguete() {}
};

#endif