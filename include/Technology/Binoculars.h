#ifndef BINOCULARS_H
#define BINOCULARS_H

#include "Technology.h"
#include "../include/Player.h"

// They just buff your sight range, requires researchers
class Binoculars : public Technology {
private:
    int visionBonus;

public:
    Binoculars() : Technology("Binoculars", 3), visionBonus(2) {}

    void onResearchComplete(Player& player) override {
        player.applyVisionBonus(visionBonus);
    }
};

#endif // BINOCULARS_H
