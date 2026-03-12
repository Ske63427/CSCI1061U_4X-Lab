#include "../include/Player.h"
#include "../include/World.h"
#include "../include/Technology/Binoculars.h"
#include "../include/Units/Researcher.h"

#include <iostream>
#include <cstdlib>

Player::Player() {
    visionBonus = 0;
    goldReserve = 10;
}

void Player::increaseGoldReserve(int goldAdded){
    goldReserve += goldAdded;
}

void Player::decreaseGoldReserve(int goldRemoved){
    goldReserve -= goldRemoved;
}

int Player::getGoldReserve() const {
    return goldReserve;
}

void Player::collectBuildingIncome() {
    for (Building* building : buildings) {
        if (building->getName() == "Gold Mine" || building->getName() == "Gold Panner") {
            goldReserve += 2;
        }
    }
}

void Player::addUnit(Unit* unit) {
    units.push_back(unit);
}

void Player::addBuilding (Building* building){
    buildings.push_back(building);
}

const std::vector<Unit*>& Player::getUnits() const {
    return units;
}

void Player::startBinocularsResearch() {
    if (!canResearch()) {
        std::cout << "You need a Researcher unit to begin research.\n";
        return;
    }

    if (activeResearch || hasResearchedTechnology("Binoculars")) {
        return;
    }

    activeResearch = std::make_shared<Binoculars>();
}

void Player::advanceResearch() {
    if (!activeResearch) {
        return;
    }

    int speed = getResearchSpeed();
    if (speed == 0) {
        std::cout << "Research paused. No Researchers available.\n";
        return;
    }

    for (int tick = 0; tick < speed; ++tick) {
        bool completed = activeResearch->advanceResearch(*this);
        if (completed) {
            std::cout << activeResearch->getName() << " researched! Permanent vision bonus unlocked.\n";
            researchedTechnologies.push_back(activeResearch);
            activeResearch.reset();
            return;
        }
    }

    std::cout << "Researching " << activeResearch->getName() << " ("
              << activeResearch->getProgress() << "/" << activeResearch->getResearchTurns()
              << ") [Speed: " << speed << "]\n";
}

bool Player::hasResearchedTechnology(const std::string& technologyName) const {
    for (const std::shared_ptr<Technology>& technology : researchedTechnologies) {
        if (technology->getName() == technologyName) {
            return true;
        }
    }

    return false;
}

bool Player::isResearchInProgress() const {
    return static_cast<bool>(activeResearch);
}

void Player::applyVisionBonus(int amount) {
    visionBonus += amount;
}

int Player::getVisionBonus() const {
    return visionBonus;
}

int Player::getResearcherCount() const {
    int count = 0;
    for (Unit* unit : units) {
        if (unit->getName() == "Researcher") {
            ++count;
        }
    }
    return count;
}

bool Player::canResearch() const {
    return getResearcherCount() > 0;
}

int Player::getResearchSpeed() const {
    return getResearcherCount();
}

void Player::tryFindResearcher(World& world, int playerNumber) {
    if (getResearcherCount() >= 3) {
        return;
    }

    if ((std::rand() % 100) < 100) {
        Unit* researcher = new Researcher();
        addUnit(researcher);
        world.placeUnitRandomly(researcher, playerNumber);
        std::cout << "Player " << (playerNumber + 1) << " found a Researcher during exploration!\n";
    }
}