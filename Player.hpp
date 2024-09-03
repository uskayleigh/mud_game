// Player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Object.hpp"
#include <vector>
#include <string>

class Player {
public:
    Player(const std::string &name);

    void addObject(const Object &object);        // Add an object to the inventory
    void removeObject(const std::string &objectName); // Remove an object by name
    void showInventory() const;                 // Display the player's inventory
    Object* getObject(const std::string &objectName); // Get a pointer to an object in the inventory

private:
    std::string name;
    std::vector<Object> inventory;              // The player's inventory
};

#endif // PLAYER_HPP
