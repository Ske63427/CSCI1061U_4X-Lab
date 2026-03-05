#ifndef UNIT_H
#define UNIT_H

#include <string>

class World;

class Unit {
private:
    int sight;

public:
    explicit Unit(int sightRange) : sight(sightRange) {}
    virtual ~Unit() {}

    int getSight() const {
        return sight;
    }

    virtual std::string getName() const = 0;
    virtual void action(int playerNumber, World& world) = 0;
};

#endif // UNIT_H