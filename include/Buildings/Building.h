#ifndef BUILDING_H
#define BUILDING_H

#include <string>

class Building {
    protected:
        std::string name;
        int resourcesGenerated;

    public:
        Building(const std::string& buildingName, int resourcesGenerated)
            : name(buildingName), resourcesGenerated(resourcesGenerated) {}
        
        virtual ~Building() {}
        
        const std::string& getName() const { return name; }
        virtual int getResourceOutput() const = 0;
};

#endif