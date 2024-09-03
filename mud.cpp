#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

class Room {
public:
    std::string description;
    std::vector<std::string> players;
    std::map<std::string, Room*> exits;

    Room(const std::string &desc) : description(desc) {}

    void addPlayer(const std::string &playerName) {
        players.push_back(playerName);
    }

    void removePlayer(const std::string &playerName) {
        players.erase(std::remove(players.begin(), players.end(), playerName), players.end());
    }

    void describe() const {
        std::cout << description << std::endl;
        std::cout << "Players in the room: ";
        for (const auto &player : players) {
            std::cout << player << " ";
        }
        std::cout << std::endl;
        std::cout << "Exits: ";
        for (const auto &exit : exits) {
            std::cout << exit.first << " ";
        }
        std::cout << std::endl;
    }

    void addExit(const std::string &direction, Room *room) {
        exits[direction] = room;
    }

    Room* getExit(const std::string &direction) {
        if (exits.find(direction) != exits.end()) {
            return exits[direction];
        } else {
            return nullptr;
        }
    }
};

void saveGameState(const std::string &playerName, const std::string &currentRoomName) {
    std::ofstream file("game_state.txt");
    if (file.is_open()) {
        file << playerName << std::endl;
        file << currentRoomName << std::endl;
        file.close();
        std::cout << "Game state saved: " << playerName << " in " << currentRoomName << std::endl;
    } else {
        std::cout << "Unable to save game state." << std::endl;
    }
}

bool loadGameState(std::string &playerName, std::string &currentRoomName) {
    std::ifstream file("game_state.txt");
    if (file.is_open()) {
        std::getline(file, playerName);
        std::getline(file, currentRoomName);
        file.close();
        std::cout << "Loaded game state: " << playerName << " in " << currentRoomName << std::endl;
        return true;
    } else {
        std::cout << "No saved game state found." << std::endl;
        return false;
    }
}

int main() {
    // Updated room descriptions
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

    // Variables for player name and current room
    std::string playerName;
    Room* currentRoom = &mainRoom;

    // Try to load the game state
    std::string currentRoomName;
    if (loadGameState(playerName, currentRoomName)) {
        std::cout << "Welcome back, " << playerName << "!" << std::endl;

        // Restore the player's location based on saved state
        if (currentRoomName == "mainRoom") currentRoom = &mainRoom;
        else if (currentRoomName == "hallway") currentRoom = &hallway;
        else if (currentRoomName == "kitchen") currentRoom = &kitchen;

        currentRoom->addPlayer(playerName);
    } else {
        // Start a new game
        std::cout << "Enter your name: ";
        std::cin >> playerName;
        currentRoom->addPlayer(playerName);
    }

    // Main game loop
    std::string command;
    while (true) {
        currentRoom->describe();

        std::cout << "Enter a command (look, go <direction>, n, s, e, w, examine <furniture|object>, take <object>, save, quit): ";
        std::cin >> command;

        if (command == "look") {
            currentRoom->describe();
        } else if (command == "go") {
            std::string direction;
            std::cin >> direction;

            Room* nextRoom = currentRoom->getExit(direction);
            if (nextRoom) {
                currentRoom->removePlayer(playerName);
                currentRoom = nextRoom;
                currentRoom->addPlayer(playerName);
            } else {
                std::cout << "You can't go that way." << std::endl;
            }
        } else if (command == "n" || command == "s" || command == "e" || command == "w") {
            std::string direction;
            if (command == "n") direction = "north";
            else if (command == "s") direction = "south";
            else if (command == "e") direction = "east";
            else if (command == "w") direction = "west";

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
                std::cout << "You take the " << objectName << "." << std::endl;
                currentRoom->removeObject(objectName);
                // Here you would typically add the object to the player's inventory
            } else {
                std::cout << "There is no " << objectName << " here." << std::endl;
            }
        } else if (command == "save") {
            saveGameState(playerName, 
                          currentRoom == &mainRoom ? "mainRoom" : 
                          currentRoom == &hallway ? "hallway" : 
                          "kitchen");
            std::cout << "Game state saved." << std::endl;
        } else if (command == "quit") {
            currentRoom->removePlayer(playerName);
            saveGameState(playerName, 
                          currentRoom == &mainRoom ? "mainRoom" : 
                          currentRoom == &hallway ? "hallway" : 
                          "kitchen");
            std::cout << "Game state saved. Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}
