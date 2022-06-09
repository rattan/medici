#pragma once

#include <string>
#include <sstream>
#include <regex>

#include "rect.h"

class Display {
    Rect displayRect;
    bool _primary;
    bool _control;
    public:
    Display (const std::string &displayConfig);
    std::string toString();
};
