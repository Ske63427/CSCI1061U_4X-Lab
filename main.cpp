#include "World.h"
#include "Player.h"
#include "Plains.h"
#include "Swamp.h"
#include "Scout.h"
#include "Researcher.h"
#include "horse.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

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
        // Test setup: Player 1 starts with binoculars on their initial scout.
        Unit* scout = (i == 0) ? static_cast<Unit*>(new Scout(4)) : static_cast<Unit*>(new Scout());
        players.back().addUnit(scout);
        world.placeUnitRandomly(scout, i);

        if (i == 0) {
            std::cout << "Player 1 starting Scout is using Binoculars (sight +2).\n";
            Unit* horse = new Horse();
            players.back().addUnit(horse);
            world.placeUnitRandomly(horse, i);
            std::cout << "Player 1 starts with a Horse (3 moves, no swamps).\n";
        }
    }

    // Main game loop
    char userChoice = 'n'; // Default choice to start the game
    while (userChoice != 'y') {
        for (int i = 0; i < numberOfPlayers; ++i) {
            std::cout << "\n--- Player " << (i + 1) << " Turn ---\n";

            Scout::setPlayerVisionBonus(i, players[i].getVisionBonus());

            if (!players[i].hasResearchedTechnology("Binoculars")) {
                if (!players[i].isResearchInProgress()) {
                    char startResearch;
                    std::cout << "Start researching Binoculars? (y/n): ";
                    std::cin >> startResearch;
                    if (startResearch == 'y' || startResearch == 'Y') {
                        players[i].startBinocularsResearch();
                    }
                }

                players[i].advanceResearch();
            }

            Scout::setPlayerVisionBonus(i, players[i].getVisionBonus());

            const std::size_t unitsThisTurn = players[i].getUnits().size();
            for (std::size_t unitIndex = 0; unitIndex < unitsThisTurn; ++unitIndex) {
                Unit* unit = players[i].getUnits()[unitIndex];
                unit->action(i, world);
                players[i].tryFindResearcher(world, i);
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