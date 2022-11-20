#pragma once

#include "event.h"
#include "packet.h"
#include "point.h"

namespace med {


class MouseEvent : public Event, public Packet {
private:
    const Point _moveXY{0,0};
    const int _button;
public:
    MouseEvent(Point moveXY, int button);
    const Point& moveXY() const;
    const int moveX() const;
    const int moveY() const;
    const int button() const;
    
    virtual Index packetIndex() const;
    virtual std::vector<std::byte> boxing() const;
    virtual void unboxing(std::vector<std::byte> dataStream);
};

}
