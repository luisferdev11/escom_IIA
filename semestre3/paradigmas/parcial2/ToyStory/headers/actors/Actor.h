#ifndef ACTOR_H
#define ACTOR_H

#include <string>

class Actor {
public:
    std::string name;
    Actor(const std::string& n);
    virtual void actuar() = 0;
    virtual ~Actor() {}
};

#endif