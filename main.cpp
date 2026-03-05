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
        Player player;
        // TODO: Create a Scout and add it to the player's units 
        player.addUnit(&Scout);
        world.placeUnitRandomly(&Scout, i);
        // TODO: placeUnitRandomly in the world
        players.push_back(player);
    }

    // Main game loop
    char userChoice = 'n'; // Default choice to start the game
    while (userChoice != 'y') {
        for (int i = 0; i < numberOfPlayers; ++i) {
            
            //TODO: For each unit the player owns, activate that unit
            //tip: You may need to pass a reference to the world and the player number
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