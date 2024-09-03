#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Object.hpp"
#include <vector>
#include <string>

class Player {
public:
    Player(const std::string &name);

    void addObject(const Object &object);
    void removeObject(const std::string &objectName);
    void showInventory() const;
    Object* getObject(const std::string &objectName);

    // Methods for saving/loading inventory
    std::string serializeInventory() const;
    void deserializeInventory(const std::string &inventoryData);

private:
    std::string name;
    std::vector<Object> inventory;
};

#endif // PLAYER_HPP
