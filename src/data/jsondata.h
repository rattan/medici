#pragma once

#include "json.hpp"
#include "data.h"
#include "packet.h"

namespace med {

class JsonData: public Data, public Packet{
protected:
    const std::string toString() const;
    virtual void setJson(nlohmann::json json) = 0;
    virtual const nlohmann::json toJson() const = 0;
    
    std::vector<std::byte> boxing() const;
    void unboxing(std::vector<std::byte> dataStream);
};

}