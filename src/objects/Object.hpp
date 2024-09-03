// Object.hpp
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>

class Object {
public:
    std::string name;
    std::string description;

    Object(const std::string &name, const std::string &description);
    void describe() const;
};

#endif // OBJECT_HPP
