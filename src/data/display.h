#pragma once

#include <string>
#include <sstream>
#include <regex>

#include "jsondata.h"
#include "rect.h"
#include "../util/log.h"

#define JSON_PROPERTY_TOP "top"
#define JSON_PROPERTY_LEFT "left"
#define JSON_PROPERTY_WIDTH "width"
#define JSON_PROPERTY_HEIGHT "height"

namespace med {

class Display: public JsonData {
    Rect displayRect;
    bool _primary;
    bool _control;
    public:
    Display (const Rect &r = Rect());
    
    const std::string toString() const;
    virtual void setJson(nlohmann::json json);
    virtual const nlohmann::json toJson() const;
    virtual const std::string tag() const;
};

}
