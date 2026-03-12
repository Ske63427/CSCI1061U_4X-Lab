#pragma once

#include "Unit.h"
#include "../include/World.h"

#include <iostream>

// required to make new tech, you can just find them randomly (it is set to 100% for now tho)
class Researcher : public Unit {
public:
    Researcher() : Unit(1) {}

    std::string getName() const override { return "Researcher"; }

    void action(int playerNumber, World& world) override {
        world.displayMapWithSight(playerNumber, getSight(), this);

        std::string direction;
        while (true) {
            std::cout << "Player " << (playerNumber + 1) << " - Move Researcher (N/S/E/W): ";
            std::cin >> direction;

            if (direction != "N" && direction != "S" && direction != "E" && direction != "W") {
                std::cout << "Invalid direction.\n";
                continue;
            }

            if (world.moveUnit(this, direction, playerNumber)) {
                break;
            }

            std::cout << "Move blocked. Try again.\n";
        }
    }
};

