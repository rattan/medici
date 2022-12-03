#pragma once

#include <string>
#include <list>

#include "jsondata.h"
#include "rect.h"
#include "point.h"
#include "../util/log.h"

#define JSON_PROPERTY_TOP "top"
#define JSON_PROPERTY_LEFT "left"
#define JSON_PROPERTY_WIDTH "width"
#define JSON_PROPERTY_HEIGHT "height"

namespace med {

class Display: public JsonData {
    std::list<Rect> displayRect;
    bool _primary;
    bool _control;
    public:
    Display (const Rect &r = Rect());
    Display (const std::list<Rect> &rectList);

    bool isPositionInside(const Point &position) const;
    int count();
    
    const std::string toString() const;
    virtual void setJson(nlohmann::json json);
    virtual const nlohmann::json toJson() const;
    virtual const std::string tag() const;

    Index packetIndex() const;
};

}
