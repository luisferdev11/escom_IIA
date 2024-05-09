#ifndef TOMHANKS_H
#define TOMHANKS_H

#include "actors/Actor.h"
#include "characters/Woody.h"

class TomHanks : public Actor, public Woody {
public:
    TomHanks();
    void actuar() override;
};

#endif