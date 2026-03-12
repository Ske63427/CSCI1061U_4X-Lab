#ifndef TECHNOLOGY_H
#define TECHNOLOGY_H

#include <string>

class Player;

class Technology {
protected:
    std::string name;
    int researchTurns;
    int progress;
    bool researched;

public:
    Technology(const std::string& technologyName, int turns)
        : name(technologyName), researchTurns(turns), progress(0), researched(false) {}

    virtual ~Technology() {}

    const std::string& getName() const { return name; }
    int getProgress() const { return progress; }
    int getResearchTurns() const { return researchTurns; }
    bool isResearched() const { return researched; }

    bool advanceResearch(Player& player) {
        if (researched) {
            return false;
        }

        ++progress;
        if (progress >= researchTurns) {
            researched = true;
            onResearchComplete(player);
            return true;
        }

        return false;
    }

    virtual void onResearchComplete(Player& player) = 0;
};

#endif // TECHNOLOGY_H
