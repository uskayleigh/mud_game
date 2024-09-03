#include "furniture/Container.hpp"
#include <iostream>
#include <algorithm>

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
        std::cout << "\n>>> You open the " << name << ". <<<\n";
    } else {
        std::cout << "\n>>> The " << name << " is already open. <<<\n";
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
        std::cout << "\n>>> The " << name << " is closed. <<<\n";
        return;
    }

    if (contents.empty()) {
        std::cout << "\n>>> The " << name << " is empty. <<<\n";
    } else {
        std::cout << "\n>>> The " << name << " contains:\n";
        for (const auto &object : contents) {
            std::cout << " - " << object.name << ": " << object.description << "\n";
        }
        std::cout << " <<<\n";
    }
}

void Container::removeObject(const std::string &objectName) {
    auto it = std::remove_if(contents.begin(), contents.end(), 
        [&objectName](const Object &obj) { return obj.name == objectName; });
    if (it != contents.end()) {
        contents.erase(it, contents.end());
        std::cout << "\n>>> You take the " << objectName << " from the " << name << ". <<<\n";
    } else {
        std::cout << "\n>>> The " << objectName << " is not in the " << name << ". <<<\n";
    }
}

Object* Container::getObject(const std::string &objectName) {
    for (auto &object : contents) {
        if (object.name == objectName) {
            return &object;
        }
    }
    return nullptr;
}
