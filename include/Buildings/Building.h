#ifndef BUILDING_H
#define BUILDING_H

#include <string>

class Building {
    protected:
        std::string name;
        int resourcesGenerated;

    public:
        virtual ~Building() {}
        Building(const std::string& buildingName, int resourcesGenerated)
        : name(buildingName), resourcesGenerated(resourcesGenerated) {}  
};

#endif