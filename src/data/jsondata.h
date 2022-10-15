#pragma once

#include "json.hpp"
#include "data.h"

namespace med {

class JsonData: public Data {
protected:
    const std::string toString() const;
    virtual void setJson(nlohmann::json json) = 0;
    virtual const nlohmann::json toJson() const = 0;
};

}