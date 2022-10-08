#pragma once

#include <string>

namespace med
{

class JsonValue {
public:
    virtual std::string toString() = 0;
};
    
} // namespace med
