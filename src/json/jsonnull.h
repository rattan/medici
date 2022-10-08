#pragma once

#include <string>

#include "jsonvalue.h"

namespace med
{
    class JsonNull: public JsonValue {
        public:
        std::string toString() override;
    } jsonNull;

} // namespace med
