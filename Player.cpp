#include "Player.hpp"
#include <iostream>
#include <sstream>

Player::Player(const std::string &name) : name(name) {}

void Player::addObject(const Object &object) {
    inventory.push_back(object);
    std::cout << object.name << " has been added to your inventory." << std::endl;
}

void Player::removeObject(const std::string &objectName) {
    auto it = inventory.begin();
    while (it != inventory.end()) {
        if (it->name == objectName) {
            inventory.erase(it);
            std::cout << objectName << " has been removed from your inventory." << std::endl;
            return;
        } else {
            ++it;
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

std::string Player::serializeInventory() const {
    std::ostringstream oss;
    for (const auto &object : inventory) {
        oss << object.name << "," << object.description << ";";
    }
    return oss.str();
}

void Player::deserializeInventory(const std::string &inventoryData) {
    inventory.clear();
    std::istringstream iss(inventoryData);
    std::string item;
    while (std::getline(iss, item, ';')) {
        if (!item.empty()) {
            std::istringstream itemStream(item);
            std::string name, description;
            if (std::getline(itemStream, name, ',') && std::getline(itemStream, description)) {
                inventory.push_back(Object(name, description));
            }
        }
    }
}
