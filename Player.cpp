#include "Player.h"

Player::Player() {
    // Initialize any resources or member variables here, if necessary
}

//TODO: Add a function to add a unit (using its pointer) to the player's vector of units 
void Player::addUnit(Unit* unit) {
    units.push_back(unit);
}

// Implement other member functions as necessary
