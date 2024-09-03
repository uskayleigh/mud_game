#include "core/CommandHandler.hpp"
#include "furniture/Container.hpp"
#include "utils/utils.hpp"
#include <iostream>
#include <algorithm>

void handleCommand(const std::string &command, const std::string &itemName, 
                   Room* &currentRoom, std::string &currentRoomName, 
                   std::string &playerName, Player &player, 
                   Room &mainRoom, Room &treasureRoom) {

    if (command == "LOOK") {
        currentRoom->describe();
    } else if (command == "GO") {
        Room* nextRoom = currentRoom->getExit(itemName);
        if (nextRoom) {
            currentRoom = nextRoom;
            currentRoomName = (nextRoom == &mainRoom) ? "Main Room" : "Treasure Room";
            currentRoom->describe();  // Show the room description when entering a new room
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
        // Attempt to find the object in the room's furniture (e.g., chest)
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
        }
    } else if (command == "INVENTORY") {
        player.showInventory();
    } else if (command == "SAVE") {
        // Now using playerName instead of player.getName()
        if (saveGameState(playerName, currentRoomName, player, mainRoom, treasureRoom)) {
            std::cout << ">>> Game saved successfully. <<<\n";
        } else {
            std::cout << ">>> Failed to save the game. <<<\n";
        }
    } else if (command == "LOAD") {
        // Now using playerName instead of player.getName()
        if (loadGameState(playerName, currentRoomName, player, mainRoom, treasureRoom)) {
            std::cout << ">>> Game loaded successfully. <<<\n";
            if (currentRoomName == "Main Room") {
                currentRoom = &mainRoom;
            } else if (currentRoomName == "Treasure Room") {
                currentRoom = &treasureRoom;
            }
            currentRoom->describe();  // Show the room description after loading a game
        } else {
            std::cout << ">>> No saved game found. <<<\n";
        }
    } else if (command == "HELP") {
        std::cout << "\nAvailable commands:\n"
                  << " - LOOK: Describe the current room.\n"
                  << " - GO <direction>: Move to another room in the specified direction.\n"
                  << " - EXAMINE <furniture|object>: Examine a piece of furniture or an object.\n"
                  << " - OPEN <container>: Open a container (e.g., a chest).\n"
                  << " - TAKE <object>: Take an object and add it to your inventory.\n"
                  << " - INVENTORY: View your current inventory.\n"
                  << " - SAVE: Save the current game state.\n"
                  << " - LOAD: Load the previously saved game state.\n"
                  << " - QUIT: Exit the game.\n"
                  << " - HELP: Display this help message.\n";
    } else {
        std::cout << ">>> Unknown command. <<<\n";
    }
}
