#pragma once

#include "event.h"

class KeyboardEvent : public Event {
private:
    const int _key;
    const int _flag;
public:
    KeyboardEvent(int key, int flag);
    int key() const;
    int flag() const;
};
