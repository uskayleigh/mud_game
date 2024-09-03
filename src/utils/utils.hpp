#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "core/Player.hpp"
#include "core/Room.hpp"

// Function declarations
bool saveGameState(const std::string &playerName, const std::string &currentRoomName, const Player &player, const Room &mainRoom, const Room &treasureRoom);
bool loadGameState(std::string &playerName, std::string &currentRoomName, Player &player, Room &mainRoom, Room &treasureRoom);

#endif // UTILS_HPP
