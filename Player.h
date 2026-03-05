#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include <vector>

class Player {
private:
    //TODO: Add a vector of unit pointers
    std::vector<Unit*> units;

public:
    Player();
    //TODO: Declare a function to add a unit to the vector
    void addUnit(Unit* unit);
    const std::vector<Unit*>& getUnits() const;
    // Other member functions...
};


#endif // PLAYER_H
