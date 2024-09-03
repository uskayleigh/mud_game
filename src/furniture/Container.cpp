#include "furniture/Container.hpp"
#include <iostream>

Container::Container(const std::string &name, const std::string &description)
    : Furniture(name, description), containerOpen(false) {}

void Container::addObject(const Object &object) {
    contents.push_back(object);
}

bool Container::isOpen() const {
    return containerOpen;
}

void Container::open() {
    if (!containerOpen) {
        containerOpen = true;
        std::cout << "You open the " << name << "." << std::endl;
    } else {
        std::cout << "The " << name << " is already open." << std::endl;
    }
}

void Container::describe() const {
    std::cout << description;
    if (containerOpen) {
        std::cout << " It is open.";
    } else {
        std::cout << " It is closed.";
    }
    std::cout << std::endl;
}

void Container::describeContents() const {
    if (!containerOpen) {
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

void Container::removeObject(const std::string &objectName) {
    auto it = std::remove_if(contents.begin(), contents.end(), 
        [&objectName](const Object &obj) { return obj.name == objectName; });
    contents.erase(it, contents.end());
}

Object* Container::getObject(const std::string &objectName) {
    for (auto &object : contents) {
        if (object.name == objectName) {
            return &object;
        }
    }
    return nullptr;
}
