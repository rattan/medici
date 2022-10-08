#pragma once

#include <string>
#include <map>

#include "jsonvalue.h"
#include "jsonstring.h"

namespace med {
    class JsonObject: public JsonValue {
        std::map<JsonString, JsonValue*> value;
        public:
        std::string toString() override;
    }
}