#include "statemanager.h"

namespace med {

StateManager::StateManager() {
}

void StateManager::grabFocus(Uuid uuid) {
    this->_focused = uuid;
    for(auto config: _connections) {
        if(this->_focused == config.uuid()) {
            this->_focusedConfig = &config;
        }
    }
}

Uuid StateManager::getFocused() {
    return this->_focused;
}

void StateManager::setGlobalPosition(Point position) {
    bool canMove = false;
    if (getFocused() != Uuid::nil() 
        && this->_focusedConfig->display().isPositionInside(position)) {
        canMove = true;
    } else {
        for (auto const& config: _connections) {
            if (config.display().isPositionInside(position)) {
                grabFocus(config.uuid());
                canMove = true;
                break;
            }
        }
    }
    if (canMove) {
        this->_globalPosition.moveTo(position);
    }
}

void StateManager::moveGlobalPosition(Point delta) {
    setGlobalPosition(this->_globalPosition + delta);
}

void StateManager::setConnections(std::list<Config> connections) {
    this->_connections.clear();
    std::copy(std::begin(connections), std::end(connections), std::back_inserter(this->_connections));
}

}