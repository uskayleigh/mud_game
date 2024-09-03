#ifndef FURNITURE_HPP
#define FURNITURE_HPP

#include "Object.hpp"
#include <vector>
#include <string>

class Furniture {
public:
    Furniture(const std::string &name, const std::string &description);
    virtual void describe() const;
    std::string name;
    std::string description;
};

class Drawer : public Furniture {
public:
    Drawer(const std::string &name, const std::string &description);
    void addObject(const Object &object);
    void openDrawer();
    bool isOpen() const;
    void describeContents() const;

private:
    bool open;
    std::vector<Object> contents;
};

#endif // FURNITURE_HPP
