#include "Player.h"
#include "Binoculars.h"
#include <iostream>

Player::Player() {
    visionBonus = 0;
}

void Player::addUnit(Unit* unit) {
    units.push_back(unit);
}

const std::vector<Unit*>& Player::getUnits() const {
    return units;
}

void Player::startBinocularsResearch() {
    if (activeResearch || hasResearchedTechnology("Binoculars")) {
        return;
    }

    activeResearch = std::make_shared<BinocularsTechnology>();
}

void Player::advanceResearch() {
    if (!activeResearch) {
        return;
    }

    bool completed = activeResearch->advanceResearch(*this);
    std::cout << "Researching " << activeResearch->getName() << " ("
              << activeResearch->getProgress() << "/" << activeResearch->getResearchTurns()
              << ")\n";

    if (completed) {
        researchedTechnologies.push_back(activeResearch);
        std::cout << activeResearch->getName() << " researched. Permanent vision bonus unlocked.\n";
        activeResearch.reset();
    }
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
