#pragma once

#include <list>

#include "../data/point.h"
#include "../data/display.h"

namespace med {

class StateManager {
    bool _focused;
    Point _globalPosition;
    Point _localPosition;
    std::list<Display> _displayList;
    Display *_myDisplay;

    void grabFocus();
    void releaseFocus();
public:
    // StateManager();
    bool isFocused();

    void setGlobalPosition(Point position);
 



};

}