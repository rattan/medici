#include "display.h"

namespace med {

Display::Display(const Rect& r): displayRect(r) {}

const std::string Display::toString() const {
    return toJson().dump();
}

void Display::setJson(nlohmann::json json) {
    try {
        int top = json[JSON_PROPERTY_TOP];
        int left = json[JSON_PROPERTY_LEFT];
        int width = json[JSON_PROPERTY_WIDTH];
        int height = json[JSON_PROPERTY_HEIGHT];
        displayRect = Rect(Point(top, left), width, height);
    } catch(nlohmann::detail::type_error e) {
        Log::e(tag(), std::string(e.what()) + json.dump(4));
        displayRect = Rect();
    }
}

const nlohmann::json Display::toJson() const{
    return nlohmann::json({
        {JSON_PROPERTY_TOP, displayRect.top()},
        {JSON_PROPERTY_LEFT, displayRect.left()},
        {JSON_PROPERTY_WIDTH, displayRect.width()},
        {JSON_PROPERTY_HEIGHT, displayRect.height()}
    });
}

const std::string Display::tag() const {
    return "Display";
}

Packet::Index Display::packetIndex() const {
    return Index::DISPLAY;
}

}
