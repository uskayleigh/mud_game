#include "core/Room.hpp"
#include "core/Player.hpp"
#include "objects/Object.hpp"
#include "furniture/Furniture.hpp"
#include "furniture/Container.hpp"
#include "utils/Config.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <sstream>

int main() {
    Config config;  // Initialize the configuration
    
    // Define the rooms with both a name and a description
    Room mainRoom("Main Room", "You are in a large, empty room with stone walls. There are exits to the north and east.");
    Room treasureRoom("Treasure Room", "You are in a brightly lit room filled with glittering treasures.");
    
    // Define exits between rooms
    mainRoom.addExit("north", &treasureRoom);

    // Define objects
    Object treasure("gold coins", "A pile of shiny gold coins.");
    
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

    // Main game loop
    std::string commandLine;
    while (true) {
        currentRoom->describe();

        std::cout << "Enter a command (LOOK, GO <direction>, EXAMINE <furniture|object>, OPEN <container>, TAKE <object>, SAVE, LOAD, INVENTORY, QUIT): ";
        std::getline(std::cin, commandLine);

        std::istringstream iss(commandLine);
        std::string command, itemName;
        iss >> command;
        iss >> itemName;

        // Convert command to uppercase for consistency
        std::transform(command.begin(), command.end(), command.begin(), ::toupper);

        if (command == "LOOK") {
            currentRoom->describe();
        } else if (command == "GO") {
            Room* nextRoom = currentRoom->getExit(itemName);
            if (nextRoom) {
                currentRoom = nextRoom;
                currentRoomName = (nextRoom == &mainRoom) ? "Main Room" : "Treasure Room";
            } else {
                std::cout << "You can't go that way." << std::endl;
            }
        } else if (command == "OPEN") {
            Furniture* furn = currentRoom->getFurniture(itemName);
            if (furn) {
                Container* container = dynamic_cast<Container*>(furn);
                if (container) {
                    container->open();
                    container->describeContents();
                } else {
                    std::cout << "You can't open the " << itemName << "." << std::endl;
                }
            } else {
                std::cout << "There is no " << itemName << " here to open." << std::endl;
            }
        } else if (command == "EXAMINE") {
            Furniture* furn = currentRoom->getFurniture(itemName);
            if (furn) {
                furn->describe();

                Container* container = dynamic_cast<Container*>(furn);
                if (container && container->isOpen()) {
                    container->describeContents();
                }
            } else {
                Object* object = currentRoom->getObject(itemName);
                if (object) {
                    object->describe();
                } else {
                    std::cout << "There is no " << itemName << " here." << std::endl;
                }
            }
        } else if (command == "TAKE") {
            Container* container = dynamic_cast<Container*>(currentRoom->getFurniture(itemName));
            if (container && container->isOpen()) {
                Object* object = container->getObject(itemName);
                if (object) {
                    player.addObject(*object);
                    container->removeObject(itemName);
                    std::cout << "You take the " << itemName << "." << std::endl;
                } else {
                    std::cout << "There is no " << itemName << " in the " << container->name << "." << std::endl;
                }
            } else {
                Object* object = currentRoom->getObject(itemName);
                if (object) {
                    player.addObject(*object);
                    currentRoom->removeObject(itemName);
                    std::cout << "You take the " << itemName << "." << std::endl;
                } else {
                    std::cout << "There is no " << itemName << " here." << std::endl;
                }
            }
        } else if (command == "INVENTORY") {
            player.showInventory();
        } else if (command == "SAVE") {
            if (saveGameState(playerName, currentRoomName, player, mainRoom, treasureRoom)) {
                std::cout << "Game saved successfully." << std::endl;
            } else {
                std::cout << "Failed to save the game." << std::endl;
            }
        } else if (command == "LOAD") {
            if (loadGameState(playerName, currentRoomName, player, mainRoom, treasureRoom)) {
                std::cout << "Game loaded successfully." << std::endl;
                if (currentRoomName == "Main Room") {
                    currentRoom = &mainRoom;
                } else if (currentRoomName == "Treasure Room") {
                    currentRoom = &treasureRoom;
                }
            } else {
                std::cout << "No saved game found." << std::endl;
            }
        } else if (command == "QUIT") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}
