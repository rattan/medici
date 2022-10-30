#include "jsondata.h"

namespace med {
const std::string JsonData::toString() const {
    return toJson().dump();
}

std::vector<std::byte> JsonData::boxing() const {
    std::string jsonString = toString();
    std::vector<std::byte> result(jsonString.size());
        std::transform(std::begin(jsonString), std::end(jsonString), std::back_inserter(result), [](char c) {
        return std::byte(c);
    });
    return result;
}

void JsonData::unboxing(std::vector<std::byte> dataStream) {
    setJson(nlohmann::json::parse(std::string(reinterpret_cast<const char *>(&dataStream[0]), dataStream.size())));
}

}