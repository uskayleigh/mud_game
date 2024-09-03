// Room.cpp
#include "Room.hpp"
#include <algorithm>
#include <iostream>

// Constructor for Room
Room::Room(const std::string &desc) : description(desc) {}

// Add a player to the room
void Room::addPlayer(const std::string &playerName) {
    players.push_back(playerName);
}

// Remove a player from the room
void Room::removePlayer(const std::string &playerName) {
    players.erase(std::remove(players.begin(), players.end(), playerName), players.end());
}

// Describe the room, including players, exits, furniture, and objects
void Room::describe() const {
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

    std::cout << "Furniture in the room: ";
    for (const auto &furn : furniture) {
        std::cout << furn.name << " ";
    }
    std::cout << std::endl;

    std::cout << "Objects in the room: ";
    for (const auto &object : objects) {
        std::cout << object.name << " ";
    }
    std::cout << std::endl;
}

// Add an exit to the room
void Room::addExit(const std::string &direction, Room *room) {
    exits[direction] = room;
}

// Get the room in the direction specified
Room* Room::getExit(const std::string &direction) {
    if (exits.find(direction) != exits.end()) {
        return exits[direction];
    } else {
        return nullptr;
    }
}

// Add an object to the room
void Room::addObject(const Object &object) {
    objects.push_back(object);
}

// Add furniture to the room
void Room::addFurniture(const Furniture &furn) {
    furniture.push_back(furn);
}

// Get an object from the room by name
Object* Room::getObject(const std::string &objectName) {
    for (auto &object : objects) {
        if (object.name == objectName) {
            return &object;
        }
    }
    return nullptr;
}

// Get a piece of furniture from the room by name
Furniture* Room::getFurniture(const std::string &furnName) {
    for (auto &furn : furniture) {
        if (furn.name == furnName) {
            return &furn;
        }
    }
    return nullptr;
}

// Remove an object from the room by name
void Room::removeObject(const std::string &objectName) {
    auto it = objects.begin();
    while (it != objects.end()) {
        if (it->name == objectName) {
            it = objects.erase(it);
        } else {
            ++it;
        }
    }
}