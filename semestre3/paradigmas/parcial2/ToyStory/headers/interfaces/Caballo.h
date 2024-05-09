#ifndef CABALLO_H
#define CABALLO_H

class Caballo {
public:
    virtual void galopar() = 0;
    virtual void relinchar() = 0;
    virtual ~Caballo() {}
};

#endif