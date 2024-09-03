#include "utils.hpp"
#include <fstream>
#include <iostream>

bool loadGameState(std::string &playerName, std::string &currentRoomName, Player &player, Room &mainRoom, Room &hallway, Room &kitchen) {
    std::ifstream file("game_state.txt");
    if (file.is_open()) {
        std::getline(file, playerName);
        std::getline(file, currentRoomName);
        std::string inventoryData;
        std::getline(file, inventoryData);
        player.deserializeInventory(inventoryData);
        std::string mainRoomData, hallwayData, kitchenData;
        std::getline(file, mainRoomData);
        mainRoom.deserializeObjects(mainRoomData);
        std::getline(file, hallwayData);
        hallway.deserializeObjects(hallwayData);
        std::getline(file, kitchenData);
        kitchen.deserializeObjects(kitchenData);
        file.close();
        std::cout << "Loaded game state: " << playerName << " in " << currentRoomName << std::endl;
        return true;
    } else {
        std::cout << "No saved game state found." << std::endl;
        return false;
    }
}

void saveGameState(const std::string &playerName, const std::string &currentRoomName, const Player &player, const Room &mainRoom, const Room &hallway, const Room &kitchen) {
    std::ofstream file("game_state.txt");
    if (file.is_open()) {
        file << playerName << std::endl;
        file << currentRoomName << std::endl;
        file << player.serializeInventory() << std::endl;
        file << mainRoom.serializeObjects() << std::endl;
        file << hallway.serializeObjects() << std::endl;
        file << kitchen.serializeObjects() << std::endl;
        file.close();
        std::cout << "Game state saved: " << playerName << " in " << currentRoomName << std::endl;
    } else {
        std::cout << "Unable to save game state." << std::endl;
    }
}
