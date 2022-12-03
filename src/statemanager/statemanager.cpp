#include "statemanager.h"

namespace med {

// StateManager::StateManager()
//     : _focused(false), _localPosition(-1, -1), _globalPosition(-1, -1), _myDisplay(nullptr)
// {

// }

void StateManager::grabFocus() {
    this->_focused = true;
}

void StateManager::releaseFocus() {
    this->_focused = false;
}

bool StateManager::isFocused() {
    return this->_focused;
}

void StateManager::setGlobalPosition(Point position) {
    this->_globalPosition = position;
    if(this->_myDisplay->isPositionInside(position)) {
        grabFocus();
    } else {
        releaseFocus();
    }
}


}