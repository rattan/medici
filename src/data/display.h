#pragma once

#include <string>
#include <sstream>
#include <regex>

#include "data.h"
#include "rect.h"

namespace med {

class Display: public Data {
    Rect displayRect;
    bool _primary;
    bool _control;
    public:
    Display (const std::string &displayConfig);
    Display (const Rect &r);
    
    virtual const std::string toString() const;
    virtual const std::string tag() const;
};

}
