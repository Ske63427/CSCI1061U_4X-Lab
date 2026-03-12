#ifndef SWAMP_H
#define SWAMP_H

#include "Terrain.h"

class Swamp : public Terrain {
public:
    std::string getType() const override { return "Swamp"; }
};

#endif // SWAMP_H