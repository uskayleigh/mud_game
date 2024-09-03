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
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == objectName) {
            inventory.erase(it);
            std::cout << objectName << " has been removed from your inventory." << std::endl;
            return;
        }
    }
    std::cout << objectName << " was not found in your inventory." << std::endl;
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
