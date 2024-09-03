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
    
    // Define the rooms with both a name and a description
    Room mainRoom("Main Room", "You are in a large, empty room with stone walls. There is but a single exit to the north. It is a large iron door, unrusted though yet obviously worn well down with time. There is a signle, large, keyhole towards the centre.");
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

    // Main game loop
    std::string commandLine;
    while (true) {
        currentRoom->describe();

        std::cout << "\nEnter a command (LOOK, GO <direction>, EXAMINE <furniture|object>, OPEN <container>, TAKE <object>, INVENTORY, SAVE, LOAD, QUIT):\n> ";
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
                std::cout << ">>> You can't go that way. <<<\n";
            }
        } else if (command == "OPEN") {
            Furniture* furn = currentRoom->getFurniture(itemName);
            if (furn) {
                Container* container = dynamic_cast<Container*>(furn);
                if (container) {
                    container->open();
                    container->describeContents();
                } else {
                    std::cout << ">>> You can't open the " << itemName << ". <<<\n";
                }
            } else {
                std::cout << ">>> There is no " << itemName << " here to open. <<<\n";
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
                    std::cout << ">>> There is no " << itemName << " here. <<<\n";
                }
            }
        } else if (command == "TAKE") {
            Container* container = dynamic_cast<Container*>(currentRoom->getFurniture("chest"));
            if (container && container->isOpen()) {
                Object* object = container->getObject(itemName);
                if (object) {
                    player.addObject(*object);
                    container->removeObject(itemName);
                    std::cout << ">>> You take the " << itemName << " from the chest. <<<\n";
                } else {
                    std::cout << ">>> There is no " << itemName << " in the chest. <<<\n";
                }
            } else {
                Object* object = currentRoom->getObject(itemName);
                if (object) {
                    player.addObject(*object);
                    currentRoom->removeObject(itemName);
                    std::cout << ">>> You take the " << itemName << ". <<<\n";
                } else {
                    std::cout << ">>> There is no " << itemName << " here. <<<\n";
                }
            }
        } else if (command == "INVENTORY") {
            player.showInventory();
        } else if (command == "SAVE") {
            if (saveGameState(playerName, currentRoomName, player, mainRoom, treasureRoom)) {
                std::cout << ">>> Game saved successfully. <<<\n";
            } else {
                std::cout << ">>> Failed to save the game. <<<\n";
            }
        } else if (command == "LOAD") {
            if (loadGameState(playerName, currentRoomName, player, mainRoom, treasureRoom)) {
                std::cout << ">>> Game loaded successfully. <<<\n";
                if (currentRoomName == "Main Room") {
                    currentRoom = &mainRoom;
                } else if (currentRoomName == "Treasure Room") {
                    currentRoom = &treasureRoom;
                }
            } else {
                std::cout << ">>> No saved game found. <<<\n";
            }
        } else if (command == "QUIT") {
            std::cout << ">>> Goodbye! <<<\n";
            break;
        } else {
            std::cout << ">>> Unknown command. <<<\n";
        }
    }

    return 0;
}
