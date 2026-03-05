#ifndef SCOUT_H
#define SCOUT_H

#include "Unit.h"

class Scout : public Unit {
public:
    std::string getName() const override { return "Scout"; }
};

#endif // SCOUT_H