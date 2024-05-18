#ifndef NEDBEATTY_H
#define NEDBEATTY_H

#include "actors/Actor.h"
#include "characters/Lotso.h"

class NedBeatty : public Actor, public Lotso {
public:
    NedBeatty();
    void actuar() override;
};

#endif 