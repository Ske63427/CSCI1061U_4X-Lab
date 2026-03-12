#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "../include/Buildings/Building.h"

#include "Building.h"

class GoldMine : public Building {
    public:
        GoldMine() : Building("Gold Mine", 2) {}
};

#endif 
