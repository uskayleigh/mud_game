#include "furniture/Furniture.hpp"
#include <iostream>

Furniture::Furniture(const std::string &name, const std::string &description)
    : name(name), description(description) {}

void Furniture::describe() const {
    std::cout << description << std::endl;
}

Drawer::Drawer(const std::string &name, const std::string &description)
    : Furniture(name, description), open(false) {}

void Drawer::addObject(const Object &object) {
    contents.push_back(object);
}

void Drawer::openDrawer() {
    if (!open) {
        open = true;
        std::cout << "You pull open the " << name << "." << std::endl;
    } else {
        std::cout << "The " << name << " is already open." << std::endl;
    }
}

bool Drawer::isOpen() const {
    return open;
}

void Drawer::describe() const {
    std::cout << description;
    if (open) {
        std::cout << " The drawer is open.";
    } else {
        std::cout << " The drawer is closed.";
    }
    std::cout << std::endl;
}

void Drawer::describeContents() const {
    if (!open) {
        std::cout << "The " << name << " is closed." << std::endl;
        return;
    }

    if (contents.empty()) {
        std::cout << "The " << name << " is empty." << std::endl;
    } else {
        std::cout << "The " << name << " contains:" << std::endl;
        for (const auto &object : contents) {
            std::cout << "- " << object.name << ": " << object.description << std::endl;
        }
    }
}
