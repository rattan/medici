#pragma once

#include <string>

#include "jsonvalue.h"

namespace med
{
    class JsonBool: public JsonValue {
        bool value;
        public: 
        std::string toString() override;
    }
} // namespace med
