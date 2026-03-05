#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>

class Terrain {
public:
    virtual ~Terrain() {}
    virtual std::string getType() const = 0;
};

#endif // TERRAIN_H
// Swamps will reduce movement by half  