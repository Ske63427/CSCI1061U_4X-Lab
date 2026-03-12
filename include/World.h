#ifndef WORLD_H
#define WORLD_H

#include "../include/Terrain/Terrain.h"
#include "../include/Units/Unit.h"
#include "../include/Buildings/Building.h"

#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <string>

class Unit;


class World {
private:
    static const int size = 10; // Adjust size for demonstration
    std::vector<std::vector<Terrain*>> grid;
    //TODO: Uncomment the line below when unit is implemented 
    std::unordered_map<Unit*, std::pair<std::pair<int, int>, int>> unitPositions; // Unit to position and player mapping
    std::unordered_map<Building*, std::pair<std::pair<int, int>, int>> buildingPositions;

public:
    World();
    ~World();
    void displayMap() const;
    
    //TODO: Uncomment the lines below when Unit is implemented
    void placeUnitRandomly(Unit* unit, int playerNumber);
    bool moveUnit(Unit* unit, const std::string& direction, int playerNumber);
    void displayMapWithSight(int playerNumber, int sight, Unit* unit) const;
    bool isPositionOccupied(int x, int y) const;
    void placeBuilding(int playerNumber);
    std::string getTerrainTypeAhead(Unit* unit, const std::string& direction) const;
};

#endif // WORLD_H
