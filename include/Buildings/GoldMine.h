#ifndef GOLDMINE_H
#define GOLDMINE_H

#include "Building.h"

class GoldMine : public Building {
    public:
        GoldMine() : Building("Gold Mine", 2) {}
        int getResourceOutput() const override { return 2; }
};

#endif 
