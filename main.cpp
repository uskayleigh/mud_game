#include "Room.hpp"
#include "Player.hpp"
#include "utils.hpp"
#include "Furniture.hpp"
#include <iostream>
#include <sstream>

int main() {
    // Room descriptions
    Room mainRoom("You are in a small, dimly lit room. The walls are damp, and there is a musty smell in the air. There is a single door on the northern wall.");
    Room hallway("You are in a long, narrow hallway. There are doors on either side, north and south.");
    Room kitchen("You are in a kitchen. The smell of food fills the air. There is a single door along the southern wall.");

    // Define exits between rooms
    mainRoom.addExit("north", &hallway);
    hallway.addExit("south", &mainRoom);
    hallway.addExit("north", &kitchen);
    kitchen.addExit("south", &hallway);

    // Add furniture to the kitchen
    Drawer tableDrawer("drawer", "A small drawer built into the table.");
    tableDrawer.addObject(Object("silver key", "A small silver key, looks like it might open something important."));
    kitchen.addFurniture(tableDrawer);

    kitchen.addFurniture(Furniture("table", "A large wooden table. It is covered with various kitchen items."));

    // Add objects to the kitchen (on the table)
    kitchen.addObject(Object("cutting board", "A well-used cutting board, perfect for preparing vegetables."));
    kitchen.addObject(Object("knife", "A sharp kitchen knife, ideal for slicing and dicing."));
    kitchen.addObject(Object("bowl", "A large mixing bowl, used for preparing dough or mixing ingredients."));
    kitchen.addObject(Object("rolling pin", "A rolling pin, perfect for flattening dough."));

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

        std::cout << "Enter a command (look, go <direction>, n, s, e, w, examine <furniture|object>, open <furniture>, take <object>, inventory, save, quit): ";
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
            } else {
                std::cout << "You can't go that way." << std::endl;
            }
        } else if (command == "open") {
            Furniture* furn = currentRoom->getFurniture(itemName);
            if (furn) {
                Drawer* drawer = dynamic_cast<Drawer*>(furn);
                if (drawer) {
                    drawer->openDrawer();
                    drawer->describeContents();
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

                // Handle drawer specific actions
                if (itemName == "drawer") {
                    Drawer* drawer = dynamic_cast<Drawer*>(furn);
                    if (drawer) {
                        drawer->describeContents();
                    }
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
            Object* object = currentRoom->getObject(itemName);
            if (object) {
                player.addObject(*object);
                currentRoom->removeObject(itemName);
            } else {
                std::cout << "There is no " << itemName << " here." << std::endl;
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
        } else if (command == "quit") {
            saveGameState(playerName, 
                          currentRoom == &mainRoom ? "mainRoom" : 
                          currentRoom == &hallway ? "hallway" : 
                          "kitchen", 
                          player, mainRoom, hallway, kitchen);
            std::cout << "Game state saved. Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}
