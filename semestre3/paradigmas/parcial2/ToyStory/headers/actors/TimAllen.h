#ifndef TIMALLEN_H
#define TIMALLEN_H

#include "actors/Actor.h"
#include "characters/Buzz.h"

class TimAllen : public Actor, public Buzz {
public:
    TimAllen();
    void actuar() override;
};

#endif