#include "core/Room.hpp"
#include "core/Player.hpp"
#include "objects/Object.hpp"
#include "furniture/Furniture.hpp"
#include "furniture/Container.hpp"
#include "utils/Config.hpp"
#include "utils/utils.hpp"
#include "core/CommandHandler.hpp"  // Include the command handler
#include <iostream>
#include <sstream>
#include <algorithm>

int main() {
    Config config;  // Initialize the configuration
    
    // Define the rooms with both a name and a description
    Room mainRoom("Main Room", "You are in a large, empty room with stone walls. There is but a single exit to the north. It is a large iron door, unrusted though yet obviously worn well down with time. There is a single, large, keyhole towards the centre.");
    Room treasureRoom("Treasure Room", "You are in a brightly lit room filled with glittering treasures.");
    
    // Define exits between rooms
    mainRoom.addExit("north", &treasureRoom);
    treasureRoom.addExit("south", &mainRoom);

    // Define objects
    Object treasure("gold-coins", "A pile of shiny gold coins.");
    Object goldKey("gold-key", "A golden key, it looks mighty important.");

    // Define furniture
    Container chest("chest", "An old wooden chest with a rusty lock.");
    chest.addObject(treasure);

    // Add furniture and objects to rooms
    mainRoom.addFurniture(&chest);

    // Player setup
    std::string playerName;
    std::string currentRoomName = "Main Room";
    Room* currentRoom = &mainRoom;

    Player player("default");  // Declare and initialize player before the if statement

    // Check if saved game exists and load it
    if (loadGameState(playerName, currentRoomName, player, mainRoom, treasureRoom)) {
        std::cout << "Welcome back, " << playerName << "!" << std::endl;
        if (currentRoomName == "Main Room") {
            currentRoom = &mainRoom;
        } else if (currentRoomName == "Treasure Room") {
            currentRoom = &treasureRoom;
        }
    } else {
        std::cout << "Enter your name: ";
        std::cin >> playerName;
        player = Player(playerName);  // Initialize the player with the entered name
    }

    // Show the room description initially after loading or starting the game
    currentRoom->describe();

    // Main game loop
    std::string commandLine;
    while (true) {
        std::cout << "\nEnter a command (type 'help' for options):\n> ";
        std::getline(std::cin, commandLine);

        std::istringstream iss(commandLine);
        std::string command, itemName;
        iss >> command;
        iss >> itemName;

        // Convert command to uppercase for consistency
        std::transform(command.begin(), command.end(), command.begin(), ::toupper);

        // Handle the command using the command handler
        handleCommand(command, itemName, currentRoom, currentRoomName, playerName, player, mainRoom, treasureRoom);

        if (command == "QUIT") {
            std::cout << ">>> Goodbye! <<<\n";
            break;
        }
    }

    return 0;
}
