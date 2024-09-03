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
    
    // Room descriptions
    Room mainRoom("You are in a small, dimly lit room. The walls are damp, and there is a musty smell in the air. A single door on the northern wall leads out.");
    Room hallway("You are in a long, narrow hallway, dimly lit by flickering sconces. Doors lead north and south, and there are darkened alcoves along the walls. A sturdy chest sits against the wall.");
    Room kitchen("You are in a warm, bustling kitchen. The smell of freshly baked bread and roasting meat fills the air. There is a sturdy wooden table in the center of the room, with a small drawer built into it.");

    // Define exits between rooms
    mainRoom.addExit("north", &hallway);
    hallway.addExit("south", &mainRoom);
    hallway.addExit("north", &kitchen);
    kitchen.addExit("south", &hallway);

    // Add furniture to the kitchen
    Container tableDrawer("drawer", "A small drawer built into the table.");
    tableDrawer.addObject(Object("silver key", "A small silver key, looks like it might open something important."));
    kitchen.addFurniture(tableDrawer);

    kitchen.addFurniture(Furniture("table", "A sturdy wooden table, well-worn from years of use, sits in the center of the room."));

    // Add objects to the kitchen (on the table)
    kitchen.addObject(Object("cutting board", "A well-used cutting board, perfect for preparing vegetables."));
    kitchen.addObject(Object("knife", "A sharp kitchen knife, ideal for slicing and dicing."));
    kitchen.addObject(Object("bowl", "A large mixing bowl, used for preparing dough or mixing ingredients."));
    kitchen.addObject(Object("rolling pin", "A rolling pin, perfect for flattening dough."));

    // Add a stereotypical RPG chest to the hallway
    Container rpgChest("chest", "A sturdy chest made of oak, reinforced with iron bands. It looks like it could hold valuable items.");
    rpgChest.addObject(Object("gold coins", "A pile of shiny gold coins, the currency of adventurers."));
    rpgChest.addObject(Object("healing potion", "A small vial filled with a red liquid. It restores health."));
    rpgChest.addObject(Object("old map", "An ancient map that appears to lead to a hidden treasure."));
    hallway.addFurniture(rpgChest);

    // Player setup
    std::string playerName;
    Player player("default");  // Initial player object
    Room* currentRoom = &mainRoom;

    // Load the game state if it exists
    std::string currentRoomName;
    if (loadGameState(playerName, currentRoomName, player, mainRoom, hallway, kitchen)) {
        std::cout << "Welcome back, " << playerName << "!" << std::endl;
        if (currentRoomName == "mainRoom") currentRoom = &mainRoom;
        else if (currentRoomName == "hallway") currentRoom = &hallway;
        else if (currentRoomName == "kitchen") currentRoom = &kitchen;
    } else {
        // No saved state, starting a new game
        std::cout << "Enter your name: ";
        std::cin >> playerName;
        player = Player(playerName);
        currentRoom = &mainRoom;
    }

    // Main game loop
    std::string commandLine;
    while (true) {
        currentRoom->describe();

        std::cout << "Enter a command (look, go <direction>, n, s, e, w, examine <furniture|object>, open <furniture>, take <object>, inventory, save, autosave <on|off>, quit): ";
        std::getline(std::cin, commandLine);

        std::istringstream iss(commandLine);
        std::string command, itemName;
        iss >> command;
        iss >> itemName;

        // Handle directional shortcuts
        if (command == "n") {
            command = "go";
            itemName = "north";
        } else if (command == "s") {
            command = "go";
            itemName = "south";
        } else if (command == "e") {
            command = "go";
            itemName = "east";
        } else if (command == "w") {
            command = "go";
            itemName = "west";
        }

        if (command == "look") {
            currentRoom->describe();
        } else if (command == "go") {
            Room* nextRoom = currentRoom->getExit(itemName);
            if (nextRoom) {
                currentRoom->removePlayer(playerName);
                currentRoom = nextRoom;
                currentRoom->addPlayer(playerName);

                // Autosave if enabled
                if (config.autosaveEnabled) {
                    saveGameState(playerName, 
                                  currentRoom == &mainRoom ? "mainRoom" : 
                                  currentRoom == &hallway ? "hallway" : 
                                  "kitchen", 
                                  player, mainRoom, hallway, kitchen);
                    std::cout << "Game state autosaved." << std::endl;
                }
            } else {
                std::cout << "You can't go that way." << std::endl;
            }
        } else if (command == "open") {
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
        } else if (command == "examine") {
            Furniture* furn = currentRoom->getFurniture(itemName);
            if (furn) {
                furn->describe();

                // Handle container-specific actions
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
        } else if (command == "take") {
            Furniture* furn = currentRoom->getFurniture(itemName);
            if (furn) {
                Container* container = dynamic_cast<Container*>(furn);
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
                    std::cout << "You can't take items from a closed " << itemName << "." << std::endl;
                }
            } else {
                Object* object = currentRoom->getObject(itemName);
                if (object) {
                    player.addObject(*object);
                    currentRoom->removeObject(itemName);

                    // Autosave if enabled
                    if (config.autosaveEnabled) {
                        saveGameState(playerName, 
                                      currentRoom == &mainRoom ? "mainRoom" : 
                                      currentRoom == &hallway ? "hallway" : 
                                      "kitchen", 
                                      player, mainRoom, hallway, kitchen);
                        std::cout << "Game state autosaved." << std::endl;
                    }
                } else {
                    std::cout << "There is no " << itemName << " here." << std::endl;
                }
            }
        } else if (command == "inventory") {
            player.showInventory();
        } else if (command == "save") {
            saveGameState(playerName, 
                          currentRoom == &mainRoom ? "mainRoom" : 
                          currentRoom == &hallway ? "hallway" : 
                          "kitchen", 
                          player, mainRoom, hallway, kitchen);
            std::cout << "Game state saved." << std::endl;
        } else if (command == "autosave") {
            if (itemName == "on") {
                config.autosaveEnabled = true;
                std::cout << "Autosave enabled." << std::endl;
            } else if (itemName == "off") {
                config.autosaveEnabled = false;
                std::cout << "Autosave disabled." << std::endl;
            } else {
                std::cout << "Invalid option for autosave. Use 'autosave on' or 'autosave off'." << std::endl;
            }
        } else if (command == "quit") {
            if (config.autosaveEnabled) {
                saveGameState(playerName, 
                              currentRoom == &mainRoom ? "mainRoom" : 
                              currentRoom == &hallway ? "hallway" : 
                              "kitchen", 
                              player, mainRoom, hallway, kitchen);
                std::cout << "Game state saved. Goodbye!" << std::endl;
            }
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}
