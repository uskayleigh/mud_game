// Furniture.hpp
#ifndef FURNITURE_HPP
#define FURNITURE_HPP

#include <string>

class Furniture {
public:
    std::string name;
    std::string description;

    Furniture(const std::string &name, const std::string &description);
    void describe() const;
};

#endif // FURNITURE_HPP
