#ifndef UTILS_HPP
#define UTILS_HPP

#include "Player.hpp"
#include "Room.hpp"
#include <string>

void saveGameState(const std::string &playerName, const std::string &currentRoomName, const Player &player, const Room &mainRoom, const Room &hallway, const Room &kitchen);
bool loadGameState(std::string &playerName, std::string &currentRoomName, Player &player, Room &mainRoom, Room &hallway, Room &kitchen);

#endif // UTILS_HPP
