#pragma once

#include <string>

class Data {
public:
    virtual std::string toString() const = 0;
    virtual std::string tag() const = 0;
};
