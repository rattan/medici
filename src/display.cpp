#include "display.h"

Display::Display (const std::string &displayConfig) {
    std::regex displayConfigRe(R"((\d+) (\d+) (\d+) (\d+))");
    std::smatch match;
    if(std::regex_search(displayConfig, match, displayConfigRe)) {
        new(&displayRect) Rect(std::stoi(match[1].str()), std::stoi(match[2].str()), std::stoi(match[3].str()), std::stoi(match[4].str()));
    }
    if(displayConfig.find("primary") >0) {
        this->_primary = true;
    }
}