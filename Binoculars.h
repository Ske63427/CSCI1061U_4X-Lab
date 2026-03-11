#ifndef BINOCULARS_H
#define BINOCULARS_H

#include "Technology.h"
#include "Player.h"

class BinocularsTechnology : public Technology {
private:
    int visionBonus;

public:
    BinocularsTechnology() : Technology("Binoculars", 3), visionBonus(2) {}

    void onResearchComplete(Player& player) override {
        player.applyVisionBonus(visionBonus);
    }
};

#endif // BINOCULARS_H
