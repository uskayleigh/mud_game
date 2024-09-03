// Furniture.cpp
#include "Furniture.hpp"
#include <iostream>

Furniture::Furniture(const std::string &name, const std::string &description) 
    : name(name), description(description) {}

void Furniture::describe() const {
    std::cout << "You see " << name << ". " << description << std::endl;
}
