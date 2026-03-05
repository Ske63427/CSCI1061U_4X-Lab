#ifndef WORLD_H
#define WORLD_H

#include "Terrain.h"
#include "Unit.h"
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <string>

class World {
private:
    static const int size = 10; // Adjust size for demonstration
    std::vector<std::vector<Terrain*>> grid;
    //TODO: Uncomment the line below when unit is implemented 
    std::unordered_map<Unit*, std::pair<std::pair<int, int>, int>> unitPositions; // Unit to position and player mapping

public:
    World();
    ~World();
    void displayMap() const;
    
    //TODO: Uncomment the lines below when Unit is implemented
    void placeUnitRandomly(Unit* unit, int playerNumber);
    bool moveUnit(Unit* unit, const std::string& direction, int playerNumber);
    void displayMapWithSight(int playerNumber, int sight, Unit* unit) const;
    bool isPositionOccupied(int x, int y) const;
};

#endif // WORLD_H
