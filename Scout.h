#ifndef SCOUT_H
#define SCOUT_H

#include "Unit.h"
#include "World.h"
#include <iostream>
#include <map>

class Scout : public Unit {
public:
    explicit Scout(int sightRange = 2) : Unit(sightRange) {}

    static void setPlayerVisionBonus(int playerNumber, int bonus) {
        playerVisionBonuses()[playerNumber] = bonus;
    }

    std::string getName() const override { return "Scout"; }
    void action(int playerNumber, World& world) override {
        world.displayMapWithSight(playerNumber, getSight() + getPlayerVisionBonus(playerNumber), this);

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

private:
    static std::map<int, int>& playerVisionBonuses() {
        static std::map<int, int> bonuses;
        return bonuses;
    }

    static int getPlayerVisionBonus(int playerNumber) {
        std::map<int, int>& bonuses = playerVisionBonuses();
        std::map<int, int>::const_iterator bonusIt = bonuses.find(playerNumber);
        if (bonusIt == bonuses.end()) {
            return 0;
        }

        return bonusIt->second;
    }
};

#endif // SCOUT_H