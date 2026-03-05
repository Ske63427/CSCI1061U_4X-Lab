#include "World.h"
#include "Player.h"
#include "Plains.h"
#include "Swamp.h"
#include "Scout.h"
#include <vector>
#include <iostream>

int main() {
    World world;
    int numberOfPlayers;
    std::vector<Player> players;

    std::cout << "Enter the number of players (2-4): ";
    std::cin >> numberOfPlayers;
    if (numberOfPlayers < 2 || numberOfPlayers > 4) {
        std::cerr << "Invalid number of players. Exiting game.\n";
        return 1;
    }

    // Initialize players and their scouts
    for (int i = 0; i < numberOfPlayers; ++i) {
        players.emplace_back();
        Unit* scout = new Scout();
        players.back().addUnit(scout);
        world.placeUnitRandomly(scout, i);
    }

    // Main game loop
    char userChoice = 'n'; // Default choice to start the game
    while (userChoice != 'y') {
        for (int i = 0; i < numberOfPlayers; ++i) {
            std::cout << "\n--- Player " << (i + 1) << " Turn ---\n";
            const std::vector<Unit*>& units = players[i].getUnits();
            for (Unit* unit : units) {
                unit->action(i, world);
            }
        }


        // Display the world map with units after each round
        world.displayMap();

        // Ask the user if they want to continue or quit the game
        std::cout << "Do you want to quit the game? (y/n): ";
        std::cin >> userChoice;
        if(userChoice == 'y' || userChoice == 'Y') {
            break; // Exit the game loop
        }
    
    }
    
    return 0;
}