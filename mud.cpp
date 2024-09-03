#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class Room {
public:
    std::string description;
    std::vector<std::string> players;
    std::map<std::string, Room*> exits; // Exits from this room

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
int main() {
    // Create rooms
    Room mainRoom("You are in a small, dimly lit room. The walls are damp, and there is a musty smell in the air.");
    Room hallway("You are in a long, narrow hallway. There are doors on either side.");
    Room kitchen("You are in a kitchen. The smell of food fills the air.");

    // Define exits between rooms
    mainRoom.addExit("north", &hallway);
    hallway.addExit("south", &mainRoom);
    hallway.addExit("east", &kitchen);
    kitchen.addExit("west", &hallway);

    // Ask for the player's name
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    // Add the player to the starting room
    Room* currentRoom = &mainRoom;
    currentRoom->addPlayer(playerName);

    // Main game loop
    std::string command;
    while (true) {
        // Describe the current room
        currentRoom->describe();

        // Prompt the player for a command
        std::cout << "Enter a command (look, go <direction>, n, s, e, w, quit): ";
        std::cin >> command;

        // Handle the 'look' command
        if (command == "look") {
            currentRoom->describe();
        } 
        // Handle the 'go' command with a direction
        else if (command == "go") {
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
        } 
        // Handle the shortcut commands
        else if (command == "n" || command == "s" || command == "e" || command == "w") {
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
        } 
        // Handle the 'quit' command
        else if (command == "quit") {
            currentRoom->removePlayer(playerName);
            break;
        } 
        // Handle unknown commands
        else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}