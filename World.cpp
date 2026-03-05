#include "World.h"
#include "Plains.h"
#include "Swamp.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

World::World() : grid(size, std::vector<Terrain*>(size, nullptr)) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell = new Plains(); // Fill the grid with Plains for simplicity
            cell = new Swamp();
        }
    }
}

World::~World() {
    for (auto& row : grid) {
        for (auto* cell : row) {
            delete cell;
        }
    }
}

void World::displayMap() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            bool found = false;
            
            //TODO: Uncomment the code below when you have implemented Units
            for (const auto& pair : unitPositions) {
                if (pair.second.first.first == i && pair.second.first.second == j) {
                    std::cout << pair.second.second; // Display player number
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                string tile = "";
                int randNum = rand() % 2;
                tile = (randNum == 0) ? "." : "#";
                std::cout << tile;
            }
        }
        std::cout << "\n";
    }
}

//TODO: Uncomment all the code below code once Unit is implemented
void World::placeUnitRandomly(Unit* unit, int playerNumber) {
    int x, y;
    do {
        x = rand() % size;
        y = rand() % size;
    } while (isPositionOccupied(x, y));
    unitPositions[unit] = {{x, y}, playerNumber};
}

bool World::moveUnit(Unit* unit, const std::string& direction, int playerNumber) {
    auto it = unitPositions.find(unit);
    if (it == unitPositions.end() || it->second.second != playerNumber) return false;

    auto& pos = it->second.first;
    int newX = pos.first, newY = pos.second;

    if (direction == "N") newX--;
    else if (direction == "S") newX++;
    else if (direction == "E") newY++;
    else if (direction == "W") newY--;

    if (newX >= 0 && newX < size && newY >= 0 && newY < size && !isPositionOccupied(newX, newY)) {
        pos.first = newX;
        pos.second = newY;
        return true;
    }
    return false;
}

void World::displayMapWithSight(int playerNumber, int sight, Unit* unit) const {
    auto unitPos = unitPositions.find(unit);
    if (unitPos == unitPositions.end()) return;

    int unitX = unitPos->second.first.first, unitY = unitPos->second.first.second;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (std::abs(i - unitX) <= sight && std::abs(j - unitY) <= sight) {
                if (unitX == i && unitY == j) {
                    std::cout << "U"; // Current unit position
                } else if (isPositionOccupied(i, j)) {
                    std::cout << "X"; // Other units
                } else {
                    std::cout << "."; // Visible terrain
                }
            } else {
                std::cout << " "; // Out of sight
            }
        }
        std::cout << "\n";
    }
}

bool World::isPositionOccupied(int x, int y) const {
    for (const auto& pair : unitPositions) {
        if (pair.second.first.first == x && pair.second.first.second == y) {
            return true;
        }
    }
    return false;
}
