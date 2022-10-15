#include "inputmanager.h"

namespace med {

const std::string InputManager::TAG = "InputManager";

InputManager::InputManager() {
    startInternal();
}

InputManager::~InputManager() {
    stopInternal();
}

void InputManager::startInternal() {
    start();
}

void InputManager::stopInternal() {
    stop();
}

void InputManager::sendKeyEvent(KeyboardEvent keyEvent) {
    for (const auto& keyListener: this->_keyEventListener) {
        keyListener(keyEvent);
    }
}

void InputManager::sendMouseEvent(MouseEvent mouseEvent) {
    for (const auto& mouseListener: this->_mouseEventListener) {
        mouseListener(mouseEvent);
    }
}

void InputManager::addKeyEvnetListener(std::function<void(KeyboardEvent)> keyboardEvnetListener) {
    this->_keyEventListener.push_back(keyboardEvnetListener);
}
void InputManager::addMouseEvnetListener(std::function<void(MouseEvent)> mouseEvnetListener) {
    this->_mouseEventListener.push_back(mouseEvnetListener);
}
void InputManager::removeKeyEvnetListener(std::function<void(KeyboardEvent)> keyboardEvnetListener) {
    // this->_keyEventListener.erase(keyboardEvnetListener);
}
void InputManager::removeMouseEvnetListener(std::function<void(MouseEvent)> mouseEvnetListener) {
    // this->_mouseEventListener.erase(mouseEvnetListener);
}


}
