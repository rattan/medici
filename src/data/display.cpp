#include "display.h"

namespace med {

Display::Display(const Rect& r) {
    this->displayRect.push_back(r);
}

Display::Display(const std::list<Rect> &rectList) {
    std::copy_n(std::begin(rectList), rectList.size(), std::begin(this->displayRect));
}

bool Display::isPositionInside(const Point &position) const {
    for(const auto& rect: this->displayRect) {
        if(rect.inside(position)) {
            return true;
        }
    }
    return false;
}

int Display::count() {
    return this->displayRect.size();
}

const std::string Display::toString() const {
    return toJson().dump();
}

void Display::setJson(nlohmann::json json) {
    for(const auto& displayJson: json) {
        try {
            int top = displayJson[JSON_PROPERTY_TOP];
            int left = displayJson[JSON_PROPERTY_LEFT];
            int width = displayJson[JSON_PROPERTY_WIDTH];
            int height = displayJson[JSON_PROPERTY_HEIGHT];
            displayRect.push_back(Rect(Point(top, left), width, height));
        } catch(nlohmann::detail::type_error e) {
            Log::e(tag(), std::string(e.what()) + json.dump(4));
            displayRect.clear();
        }
    }
}

const nlohmann::json Display::toJson() const{
    nlohmann::json displayJson = nlohmann::json::array();
    for(const auto& rect: this->displayRect) {
        displayJson.push_back(nlohmann::json({
            {JSON_PROPERTY_TOP, rect.top()},
            {JSON_PROPERTY_LEFT, rect.left()},
            {JSON_PROPERTY_WIDTH, rect.width()},
            {JSON_PROPERTY_HEIGHT, rect.height()}
        }));
    }
    return displayJson;
}

const std::string Display::tag() const {
    return "Display";
}

Packet::Index Display::packetIndex() const {
    return Index::DISPLAY;
}

}
