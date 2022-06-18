#pragma once

#inlcude "event.h"

class MouseEvent: public Event {
private:
    int _moveY, _moveX;
    int _button;
}
