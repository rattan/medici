#pragma once

#include <string>

#include "jsonvalue.h"

namespace med {

class JsonString: public JsonValue {
    std::string value;
public:
    std::string toString() override;
};

}