#ifndef PLAYER_H
#define PLAYER_H

#include "Unit.h"
#include "Technology.h"
#include <vector>
#include <string>
#include <memory>

class Player {
private:
    std::vector<Unit*> units;
    std::vector<std::shared_ptr<Technology>> researchedTechnologies;
    std::shared_ptr<Technology> activeResearch;
    int visionBonus;

public:
    Player();

    void addUnit(Unit* unit);
    const std::vector<Unit*>& getUnits() const;

    void startBinocularsResearch();
    void advanceResearch();
    bool hasResearchedTechnology(const std::string& technologyName) const;
    bool isResearchInProgress() const;

    void applyVisionBonus(int amount);
    int getVisionBonus() const;
};


#endif // PLAYER_H
