#include "Room.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

Room::Room(const std::string& name, const std::string& description)
    : name(name), description(description) {}

// Adds an exit to another room and marks it as unlocked by default
void Room::addExit(const std::string& direction, Room* room) {
    exits[direction] = room;
    lockedExits[direction] = false;
}

// Locks the specified exit
void Room::lockExit(const std::string& direction) {
    if (exits.find(direction) != exits.end()) {
        lockedExits[direction] = true;
    }
}

// Unlocks the specified exit
void Room::unlockExit(const std::string& direction) {
    if (exits.find(direction) != exits.end()) {
        lockedExits[direction] = false;
    }
}

// Checks if the specified exit is locked
bool Room::isExitLocked(const std::string& direction) const {
    auto it = lockedExits.find(direction);
    return it != lockedExits.end() && it->second;
}

// Retrieves the room an exit leads to, or nullptr if locked
Room* Room::getExit(const std::string& direction) const {
    if (isExitLocked(direction)) {
        std::cout << "The door to the " << direction << " is locked.\n";
        return nullptr;
    }

    auto it = exits.find(direction);
    return it != exits.end() ? it->second : nullptr;
}

// Adds an object to the room
void Room::addObject(const Object& object) {
    objects.push_back(object);
}

// Adds furniture to the room
void Room::addFurniture(Furniture* furn) {
    furniture.push_back(furn);
}

// Retrieves an object in the room by name
Object* Room::getObject(const std::string& objectName) {
    auto it = std::find_if(objects.begin(), objects.end(),
                           [&objectName](const Object& obj) {
                               return obj.name == objectName;
                           });
    return it != objects.end() ? &(*it) : nullptr;
}

// Retrieves furniture in the room by name
Furniture* Room::getFurniture(const std::string& furnName) {
    auto it = std::find_if(furniture.begin(), furniture.end(),
                           [&furnName](Furniture* furn) {
                               return furn->name == furnName;
                           });
    return it != furniture.end() ? *it : nullptr;
}

// Removes an object from the room by name
void Room::removeObject(const std::string& objectName) {
    objects.erase(std::remove_if(objects.begin(), objects.end(),
                                 [&objectName](const Object& obj) {
                                     return obj.name == objectName;
                                 }),
                  objects.end());
}

// Serializes objects in the room to a string
std::string Room::serializeObjects() const {
    std::ostringstream oss;
    for (const auto& object : objects) {
        oss << object.name << "," << object.description << ";";
    }
    return oss.str();
}

// Deserializes a string of objects and adds them to the room
void Room::deserializeObjects(const std::string& objectData) {
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

// Describes the room, its contents, and exits
void Room::describe() const {
    std::cout << description << std::endl;

    if (!furniture.empty()) {
        std::cout << "Furniture in the room:" << std::endl;
        for (const auto& furn : furniture) {
            std::cout << " - " << furn->name << std::endl;
        }
    }

    if (!objects.empty()) {
        std::cout << "Objects in the room:" << std::endl;
        for (const auto& object : objects) {
            std::cout << " - " << object.name << std::endl;
        }
    }

    std::cout << "Exits: ";
    for (const auto& exit : exits) {
        std::cout << exit.first << " ";
    }
    std::cout << std::endl;
}
