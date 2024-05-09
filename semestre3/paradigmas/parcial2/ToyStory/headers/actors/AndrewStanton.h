#ifndef ANDREWSTANTON_H
#define ANDREWSTANTON_H

#include "actors/Actor.h"
#include "characters/Zurg.h"

class AndrewStanton : public Actor, public Zurg {
public:
    AndrewStanton();
    void actuar() override;
};

#endif