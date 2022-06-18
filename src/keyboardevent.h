#pragma once

#include "event.h"

class KeyboardEvent: public Event {
private:
    int _key;
    int _flag;
}
