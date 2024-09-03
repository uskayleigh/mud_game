// Object.cpp
#include "objects/Object.hpp"
#include <iostream>

Object::Object(const std::string &name, const std::string &description) 
    : name(name), description(description) {}

void Object::describe() const {
    std::cout << "You see a " << name << ". " << description << std::endl;
}
