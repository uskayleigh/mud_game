// Player.cpp
#include "Player.hpp"
#include <iostream>
#include <algorithm>

Player::Player(const std::string &name) : name(name) {}

void Player::addObject(const Object &object) {
    inventory.push_back(object);
    std::cout << object.name << " has been added to your inventory." << std::endl;
}

void Player::removeObject(const std::string &objectName) {
    auto it = std::remove_if(inventory.begin(), inventory.end(),
                             [objectName](const Object& obj) {
                                 return obj.name == objectName;
                             });
    if (it != inventory.end()) {
        inventory.erase(it, inventory.end());
        std::cout << objectName << " has been removed from your inventory." << std::endl;
    } else {
        std::cout << objectName << " was not found in your inventory." << std::endl;
    }
}

void Player::showInventory() const {
    std::cout << "Your inventory contains:" << std::endl;
    for (const auto &object : inventory) {
        std::cout << "- " << object.name << ": " << object.description << std::endl;
    }
    if (inventory.empty()) {
        std::cout << "Your inventory is empty." << std::endl;
    }
}

Object* Player::getObject(const std::string &objectName) {
    for (auto &object : inventory) {
        if (object.name == objectName) {
            return &object;
        }
    }
    return nullptr;
}
