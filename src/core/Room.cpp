#include "core/Room.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>

Room::Room(const std::string &desc) : description(desc) {}

void Room::addPlayer(const std::string &playerName) {
    players.push_back(playerName);
}

void Room::removePlayer(const std::string &playerName) {
    players.erase(std::remove(players.begin(), players.end(), playerName), players.end());
}

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

void Room::addExit(const std::string &direction, Room *room) {
    exits[direction] = room;
}

Room* Room::getExit(const std::string &direction) {
    if (exits.find(direction) != exits.end()) {
        return exits[direction];
    } else {
        return nullptr;
    }
}

void Room::addObject(const Object &object) {
    objects.push_back(object);
}

void Room::addFurniture(const Furniture &furn) {
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
        if (furn.name == furnName) {
            return &furn;
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
