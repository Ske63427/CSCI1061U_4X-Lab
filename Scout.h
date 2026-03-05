#ifndef SCOUT_H
#define SCOUT_H

#include "Unit.h"
#include "World.h"
#include <iostream>

class Scout : public Unit {
public:
    Scout() : Unit(2) {}

    std::string getName() const override { return "Scout"; }
    void action(int playerNumber, World& world) override {
        world.displayMapWithSight(playerNumber, getSight(), this);

        std::string direction;
        while (true) {
            std::cout << "Player " << (playerNumber + 1) << " - Move Scout (N/S/E/W): ";
            std::cin >> direction;

            if (direction != "N" && direction != "S" && direction != "E" && direction != "W") {
                std::cout << "Invalid direction. Please choose N, S, E, or W.\n";
                continue;
            }

            if (world.moveUnit(this, direction, playerNumber)) {
                break;
            }

            std::cout << "Move blocked. Try a different direction.\n";
        }
    }
};

#endif // SCOUT_H