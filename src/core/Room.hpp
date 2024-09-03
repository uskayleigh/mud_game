#ifndef ROOM_HPP
#define ROOM_HPP

#include "objects/Object.hpp"
#include "furniture/Furniture.hpp"
#include <string>
#include <map>
#include <vector>

class Room {
public:
    Room(const std::string &name, const std::string &description);

    void addExit(const std::string &direction, Room *room);
    Room* getExit(const std::string &direction) const;

    void addObject(const Object &object);
    void addFurniture(Furniture *furn);
    
    Object* getObject(const std::string &objectName);
    Furniture* getFurniture(const std::string &furnitureName);
    
    void removeObject(const std::string &objectName);
    void describe() const;

    // Serialize and deserialize room objects
    std::string serializeObjects() const;  // Declaration added
    void deserializeObjects(const std::string &objectData);  // Declaration added

    void addPlayer(const std::string &playerName);
    void removePlayer(const std::string &playerName);

private:
    std::string name;
    std::string description;
    std::map<std::string, Room*> exits;
    std::vector<Object> objects;
    std::vector<Furniture*> furniture;
    std::vector<std::string> players;  // For managing players in the room
};

#endif // ROOM_HPP
