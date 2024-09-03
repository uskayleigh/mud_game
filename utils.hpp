// utils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

void saveGameState(const std::string &playerName, const std::string &currentRoomName);
bool loadGameState(std::string &playerName, std::string &currentRoomName);

#endif // UTILS_HPP
