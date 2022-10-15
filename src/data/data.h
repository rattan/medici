#pragma once

#include <string>

class Data {
public:
    virtual const std::string toString() const = 0;
    virtual const std::string tag() const = 0;
};
