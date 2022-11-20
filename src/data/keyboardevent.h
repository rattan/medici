#pragma once

#include "event.h"
#include "packet.h"

namespace med {


class KeyboardEvent : public Event, public Packet{
private:
    const int _key;
    const int _flag;
public:
    KeyboardEvent(int key, int flag);
    int key() const;
    int flag() const;

    virtual Index packetIndex() const;
    virtual std::vector<std::byte> boxing() const;
    virtual void unboxing(std::vector<std::byte> dataStream);
};

}
