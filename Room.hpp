#ifndef ROOM_HPP
#define ROOM_HPP

#include "Object.hpp"
#include "Furniture.hpp"
#include <vector>
#include <map>
#include <string>

class Room {
public:
    Room(const std::string &desc);

    void addPlayer(const std::string &playerName);
    void removePlayer(const std::string &playerName);
    void describe() const;
    void addExit(const std::string &direction, Room *room);
    Room* getExit(const std::string &direction);
    void addObject(const Object &object);
    void addFurniture(const Furniture &furn);
    Object* getObject(const std::string &objectName);
    Furniture* getFurniture(const std::string &furnName);
    void removeObject(const std::string &objectName);

    // Methods for saving/loading room state
    std::string serializeObjects() const;
    void deserializeObjects(const std::string &objectData);

private:
    std::string description;
    std::vector<std::string> players;
    std::map<std::string, Room*> exits;
    std::vector<Object> objects;
    std::vector<Furniture> furniture;
};

#endif // ROOM_HPP
