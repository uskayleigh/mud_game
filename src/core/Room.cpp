#include "core/Room.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>  // For std::setw

Room::Room(const std::string &name, const std::string &desc) 
    : name(name), description(desc) {}

void Room::addPlayer(const std::string &playerName) {
    players.push_back(playerName);
}

void Room::removePlayer(const std::string &playerName) {
    players.erase(std::remove(players.begin(), players.end(), playerName), players.end());
}

void Room::describe() const {
    std::cout << "\n====================== Room Description ======================\n";
    std::cout << description << "\n\n";

    // Display players in the room
    if (!players.empty()) {
        std::cout << "Players in the room:\n";
        for (const auto &player : players) {
            std::cout << " - " << player << std::endl;
        }
        std::cout << "\n";
    }

    // Display exits
    std::cout << "Exits:\n";
    for (const auto &exit : exits) {
        std::cout << " - " << exit.first << std::endl;
    }
    std::cout << "\n";

    // Display furniture in the room
    if (!furniture.empty()) {
        std::cout << "Furniture in the room:\n";
        for (const auto &furn : furniture) {
            std::cout << " - " << furn->name << std::endl;  // Use -> to access the name
        }
        std::cout << "\n";
    }

    // Display objects in the room
    if (!objects.empty()) {
        std::cout << "Objects in the room:\n";
        for (const auto &object : objects) {
            std::cout << " - " << object.name << std::endl;
        }
        std::cout << "\n";
    }

    std::cout << "==============================================================\n\n";
}

void Room::addExit(const std::string &direction, Room *room) {
    exits[direction] = room;
}

Room* Room::getExit(const std::string &direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    }
    return nullptr;
}

void Room::addObject(const Object &object) {
    objects.push_back(object);
}

void Room::addFurniture(Furniture *furn) {
    furniture.push_back(furn);
}

Object* Room::getObject(const std::string &objectName) {
    for (auto &object : objects) {
        if (object.name == objectName) {
            return &object;
        }
    }
    return nullptr;
}

Furniture* Room::getFurniture(const std::string &furnName) {
    for (auto &furn : furniture) {
        if (furn->name == furnName) {  // Use -> to access the name
            return furn;
        }
    }
    return nullptr;
}

void Room::removeObject(const std::string &objectName) {
    auto it = objects.begin();
    while (it != objects.end()) {
        if (it->name == objectName) {
            it = objects.erase(it);
            std::cout << objectName << " has been removed from the room." << std::endl;
            return;
        } else {
            ++it;
        }
    }
    std::cout << objectName << " was not found in the room." << std::endl;
}

std::string Room::serializeObjects() const {
    std::ostringstream oss;
    for (const auto &object : objects) {
        oss << object.name << "," << object.description << ";";
    }
    return oss.str();
}

void Room::deserializeObjects(const std::string &objectData) {
    objects.clear();
    std::istringstream iss(objectData);
    std::string item;
    while (std::getline(iss, item, ';')) {
        if (!item.empty()) {
            std::istringstream itemStream(item);
            std::string name, description;
            if (std::getline(itemStream, name, ',') && std::getline(itemStream, description)) {
                objects.push_back(Object(name, description));
            }
        }
    }
}
