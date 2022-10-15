#include "jsondata.h"

namespace med {
const std::string JsonData::toString() const {
    return toJson().dump();
}
}