#include "core/CommandHandler.hpp"  // Include the command handler
#include "core/rooms/MainRoom.hpp"   // Include the rooms
#include "core/rooms/TreasureRoom.hpp"
#include "core/Room.hpp"
#include "core/Player.hpp"
#include "objects/Object.hpp"
#include "furniture/Furniture.hpp"
#include "furniture/Container.hpp"
#include "utils/Config.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

int main() {
    Config config;  // Initialize the configuration
    
    // Create room instances
    MainRoom mainRoom;
    TreasureRoom treasureRoom;
    
    // Define exits between rooms
    mainRoom.addExit("north", &treasureRoom);
    treasureRoom.addExit("south", &mainRoom);

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