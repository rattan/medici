#pragma once

#include <list>

#include "../data/uuid.h"
#include "../data/config.h"
#include "../data/point.h"
#include "../data/display.h"

namespace med {

class StateManager {
    friend class DependencySet;
    Uuid _focused = Uuid::nil();
    Config *_focusedConfig = nullptr;
    Point _globalPosition;
    std::list<Config> _connections;

    void grabFocus(Uuid uuid);
    StateManager();
public:
    Uuid getFocused();
    void setGlobalPosition(Point position);
    void moveGlobalPosition(Point delta);
    void setConnections(std::list<Config> connections);
};

}