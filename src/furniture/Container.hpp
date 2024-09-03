#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "furniture/Furniture.hpp"
#include "objects/Object.hpp"
#include <vector>
#include <string>

class Container : public Furniture {
public:
    Container(const std::string &name, const std::string &description);
    
    void addObject(const Object &object);           // Add an object to the container
    bool isOpen() const;                            // Check if the container is open
    void open();                                    // Open the container
    void describe() const override;                 // Describe the container (overrides Furniture::describe)
    void describeContents() const;                  // Describe the contents of the container
    void removeObject(const std::string &objectName); // Remove an object from the container
    Object* getObject(const std::string &objectName); // Get an object from the container

private:
    bool containerOpen;             // Whether the container is open or not
    std::vector<Object> contents;   // The contents of the container
};

#endif // CONTAINER_HPP