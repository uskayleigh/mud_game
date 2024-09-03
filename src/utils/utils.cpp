#include "utils/utils.hpp"
#include "core/Room.hpp"
#include "core/Player.hpp"
#include <fstream>
#include <iostream>

bool saveGameState(const std::string &playerName, const std::string &currentRoomName, const Player &player, const Room &mainRoom, const Room &treasureRoom) {
    std::ofstream saveFile("savegame.txt");
    if (!saveFile) {
        std::cerr << "Error: Could not open save file for writing." << std::endl;
        return false;
    }

    saveFile << playerName << "\n";
    saveFile << currentRoomName << "\n";
    saveFile << player.serializeInventory() << "\n";
    saveFile << "Main Room Objects:\n" << mainRoom.serializeObjects() << "\n";
    saveFile << "Treasure Room Objects:\n" << treasureRoom.serializeObjects() << "\n";
    saveFile.close();
    return true;
}

bool loadGameState(std::string &playerName, std::string &currentRoomName, Player &player, Room &mainRoom, Room &treasureRoom) {
    std::ifstream loadFile("savegame.txt");
    if (!loadFile) {
        std::cerr << "Error: Could not open save file for reading." << std::endl;
        return false;
    }

    std::getline(loadFile, playerName);
    std::getline(loadFile, currentRoomName);
    
    std::string inventoryData;
    std::getline(loadFile, inventoryData);
    player.deserializeInventory(inventoryData);

    std::string line;
    while (std::getline(loadFile, line)) {
        if (line == "Main Room Objects:") {
            std::string objectData;
            std::getline(loadFile, objectData);
            mainRoom.deserializeObjects(objectData);
        } else if (line == "Treasure Room Objects:") {
            std::string objectData;
            std::getline(loadFile, objectData);
            treasureRoom.deserializeObjects(objectData);
        }
    }

    loadFile.close();
    return true;
}
