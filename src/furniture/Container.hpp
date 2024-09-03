#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "furniture/Furniture.hpp"
#include "objects/Object.hpp"
#include <vector>
#include <string>

class Container : public Furniture {
public:
    Container(const std::string &name, const std::string &description);
    void addObject(const Object &object);
    bool isOpen() const;
    void open();
    void describe() const override;  // Override to include container-specific description
    void describeContents() const;
    void removeObject(const std::string &objectName);
    Object* getObject(const std::string &objectName);

private:
    bool containerOpen;  // Renamed from 'open' to 'containerOpen' to avoid conflict
    std::vector<Object> contents;
};

#endif // CONTAINER_HPP
