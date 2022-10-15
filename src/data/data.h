#pragma once

#include <string>

#include "json.hpp"

class Data {
protected:
    virtual const std::string tag() const = 0;
    virtual const std::string toString() const = 0;
};
