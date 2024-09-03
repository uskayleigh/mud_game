#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <map>
#include <vector>
#include "furniture/Furniture.hpp"
#include "objects/Object.hpp"

/**
 * @brief Represents a room in the game world, containing furniture, objects, and exits.
 */
class Room {
public:
    Room(const std::string& name, const std::string& description);

    // Adds an exit to another room in a specified direction
    void addExit(const std::string& direction, Room* room);

    // Locks and unlocks an exit in a specified direction
    void lockExit(const std::string& direction);
    void unlockExit(const std::string& direction);

    // Checks if an exit is locked
    bool isExitLocked(const std::string& direction) const;

    // Retrieves the room an exit leads to, considering if it's locked
    Room* getExit(const std::string& direction) const;

    // Adds objects and furniture to the room
    void addObject(const Object& object);
    void addFurniture(Furniture* furniture);

    // Retrieves objects and furniture by name
    Object* getObject(const std::string& objectName);
    Furniture* getFurniture(const std::string& furnName);

    // Removes an object from the room by name
    void removeObject(const std::string& objectName);

    // Serializes and deserializes objects in the room
    std::string serializeObjects() const;
    void deserializeObjects(const std::string& objectData);

    // Describes the room's contents and exits
    void describe() const;

private:
    std::string name;
    std::string description;
    std::map<std::string, Room*> exits;
    std::map<std::string, bool> lockedExits; // Tracks locked exits
    std::vector<Object> objects;
    std::vector<Furniture*> furniture;
};

#endif // ROOM_HPP
