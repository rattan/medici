#pragma once

#include <string>
#include <vector>

#include "jsonvalue.h"

namespace med {
    class JsonArray: public JsonValue {
        std::vector<JsonValue*> value;
        public:
        std::string toString() override;
    }
}