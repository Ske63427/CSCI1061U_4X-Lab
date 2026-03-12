#ifndef PLAYER_H
#define PLAYER_H

#include "../include/Units/Unit.h"
#include "../include/Technology/Technology.h"

#include <vector>
#include <string>
#include <memory>

class World;

class Player {
    std::vector<Unit*> units;
    std::vector<Building*> buildings;
    std::vector<std::shared_ptr<Technology>> researchedTechnologies;
    std::shared_ptr<Technology> activeResearch;
    int visionBonus;

    public:
        Player();

        void addBuilding (Building* building);
        
        void addUnit(Unit* unit);
        const std::vector<Unit*>& getUnits() const;

        void startBinocularsResearch();
        void advanceResearch();
        bool hasResearchedTechnology(const std::string& technologyName) const;
        bool isResearchInProgress() const;

        void applyVisionBonus(int amount);
        int getVisionBonus() const;
        int getResearcherCount() const;
        bool canResearch() const;
        int getResearchSpeed() const;
        void tryFindResearcher(World& world, int playerNumber);
};

#endif // PLAYER_H
