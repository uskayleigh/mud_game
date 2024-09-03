#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include "core/Room.hpp"
#include "core/Player.hpp"
#include <string>

// Function to handle commands
void handleCommand(const std::string &command, const std::string &itemName, 
                   Room* &currentRoom, std::string &currentRoomName, 
                   std::string &playerName, Player &player, 
                   Room &mainRoom, Room &treasureRoom);

#endif // COMMANDHANDLER_HPP
