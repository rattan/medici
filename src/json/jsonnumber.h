#pragma once

#include <string>

#include "jsonvalue.h"

namespace med {
    class JsonNumber: public JsonValue {
        union {
            long long integer;
            long double floating;
        } value;
    public:
        std::string toString() override;
    };
}