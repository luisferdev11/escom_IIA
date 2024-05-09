#include "actors/AndrewStanton.h"

#include <iostream>

AndrewStanton::AndrewStanton() : Actor("Andrew Stanton") {}

void AndrewStanton::actuar() {
    std::cout << name << " está actuando como Zurg." << std::endl;
    destruir();
}