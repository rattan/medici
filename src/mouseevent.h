#pragma once

#include "event.h"
#include "point.h"

namespace med {


class MouseEvent : public Event {
private:
    const Point _moveXY{0,0};
    const int _button;
public:
    MouseEvent(Point moveXY, int button);
    const Point& moveXY() const;
    const int moveX() const;
    const int moveY() const;
    const int button() const;
};

}
