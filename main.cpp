#include "Room.hpp"
#include "Player.hpp"
#include "utils.hpp"
#include <iostream>

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
    std::string command;
    while (true) {
        currentRoom->describe();

        std::cout << "Enter a command (look, go <direction>, n, s, e, w, examine <furniture|object>, take <object>, inventory, save, quit): ";
        std::cin >> command;

        // Handle directional shortcuts
        if (command == "n") {
            command = "go north";
        } else if (command == "s") {
            command = "go south";
        } else if (command == "e") {
            command = "go east";
        } else if (command == "w") {
            command = "go west";
        }

        if (command == "look") {
            currentRoom->describe();
        } else if (command.substr(0, 3) == "go ") {
            std::string direction = command.substr(3);

            Room* nextRoom = currentRoom->getExit(direction);
            if (nextRoom) {
                currentRoom->removePlayer(playerName);
                currentRoom = nextRoom;
                currentRoom->addPlayer(playerName);
            } else {
                std::cout << "You can't go that way." << std::endl;
            }
        } else if (command == "examine") {
            std::string itemName;
            std::cin >> itemName;

            Furniture* furn = currentRoom->getFurniture(itemName);
            if (furn) {
                furn->describe();
            } else {
                Object* object = currentRoom->getObject(itemName);
                if (object) {
                    object->describe();
                } else {
                    std::cout << "There is no " << itemName << " here." << std::endl;
                }
            }
        } else if (command == "take") {
            std::string objectName;
            std::cin >> objectName;

            Object* object = currentRoom->getObject(objectName);
            if (object) {
                player.addObject(*object);
                currentRoom->removeObject(objectName);
            } else {
                std::cout << "There is no " << objectName << " here." << std::endl;
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
