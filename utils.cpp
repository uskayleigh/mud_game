// utils.cpp
#include "utils.hpp"
#include <fstream>
#include <iostream>

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
