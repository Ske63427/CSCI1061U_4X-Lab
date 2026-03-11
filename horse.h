# pragma once

#include "Unit.h"
#include "World.h"
#include <iostream>
#include <string>


// Horse's are high movemnet units. they have 3 move but cannot enter swamps.
class Horse : public Unit {
public:
    Horse() : Unit(2) {}

    std::string getName() const override { return "Horse"; }

    void action(int playerNumber, World& world) override {
        world.displayMapWithSight(playerNumber, getSight(), this);

        int movesLeft = 3;
        while (movesLeft > 0) {
            std::cout << "Player " << (playerNumber + 1)
                      << " - Move Horse (N/S/E/W) or 'D' to stop ["
                      << movesLeft << " move(s) left]: ";

            std::string direction;
            std::cin >> direction;

            if (direction == "D" || direction == "d") {
                break;
            }

            if (direction != "N" && direction != "S" && direction != "E" && direction != "W") {
                std::cout << "Invalid input. Use N/S/E/W or D to stop.\n";
                continue;
            }

            // Horses cannot enter swamp terrain
            if (world.getTerrainTypeAhead(this, direction) == "Swamp") {
                std::cout << "Horse cannot enter swamps!\n";
                continue;
            }

            if (world.moveUnit(this, direction, playerNumber)) {
                --movesLeft;
                if (movesLeft > 0) {
                    world.displayMapWithSight(playerNumber, getSight(), this);
                }
            } else {
                std::cout << "Move blocked. Try a different direction.\n";
            }
        }
    }
};

