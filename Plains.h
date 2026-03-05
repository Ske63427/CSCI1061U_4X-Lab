#ifndef PLAINS_H
#define PLAINS_H

#include "Terrain.h"

class Plains : public Terrain {
public:
    std::string getType() const override { return "Plains"; }
};

#endif // PLAINS_H
