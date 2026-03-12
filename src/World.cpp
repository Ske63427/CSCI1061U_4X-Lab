#include "../include/World.h"
#include "../include/Terrain/Plains.h"
#include "../include/Terrain/Swamp.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cctype>

using namespace std;

namespace {
    std::string getTerrainToken(const Terrain* terrain) {
        if (!terrain) {
            return "??";
        }

        const std::string type = terrain->getType();
        if (type == "Plains") {
            return "..";
        }
        if (type == "Swamp") {
            return "~~";
        }

        return "??";
    }

    std::string getUnitToken(Unit* unit, int ownerIndex) {
        if (!unit) {
            return "??";
        }

        const std::string name = unit->getName();
        char symbol = name.empty() ? '?' : static_cast<char>(std::toupper(static_cast<unsigned char>(name[0])));
        return std::string(1, symbol) + std::to_string(ownerIndex + 1);
    }
}

World::World() : grid(size, std::vector<Terrain*>(size, nullptr)) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (auto& row : grid) {
        for (auto& cell : row) {
            int randNum = rand() % 2;
            cell = (randNum == 0) ? static_cast<Terrain*>(new Plains()) : static_cast<Terrain*>(new Swamp());
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
            std::string tile = getTerrainToken(grid[i][j]);

            for (const auto& pair : unitPositions) {
                if (pair.second.first.first == i && pair.second.first.second == j) {
                    tile = getUnitToken(pair.first, pair.second.second);
                    break;
                }
            }

            std::cout << tile;
            if (j < size - 1) {
                std::cout << " ";
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

    (void)playerNumber;

    int unitX = unitPos->second.first.first, unitY = unitPos->second.first.second;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::string tile = "  ";

            if (std::abs(i - unitX) <= sight && std::abs(j - unitY) <= sight) {
                tile = getTerrainToken(grid[i][j]);

                for (const auto& pair : unitPositions) {
                    if (pair.second.first.first == i && pair.second.first.second == j) {
                        tile = getUnitToken(pair.first, pair.second.second);
                        break;
                    }
                }
            }

            std::cout << tile;
            if (j < size - 1) {
                std::cout << " ";
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

std::string World::getTerrainTypeAhead(Unit* unit, const std::string& direction) const {
    auto it = unitPositions.find(unit);
    if (it == unitPositions.end()) return "";

    int newX = it->second.first.first;
    int newY = it->second.first.second;

    if (direction == "N") newX--;
    else if (direction == "S") newX++;
    else if (direction == "E") newY++;
    else if (direction == "W") newY--;

    if (newX < 0 || newX >= size || newY < 0 || newY >= size) return "";

    return grid[newX][newY] ? grid[newX][newY]->getType() : "";
}
