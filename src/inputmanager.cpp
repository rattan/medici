#include "inputmanager.h"

namespace med {

const std::string InputManager::TAG = "InputManager";

InputManager::InputManager() {
    start();
}

InputManager::~InputManager() {
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
    this->_keyEventListener.insert(keyboardEvnetListener);
}
void InputManager::addMouseEvnetListener(std::function<void(MouseEvent)> mouseEvnetListener) {
    this->_mouseEventListener.insert(mouseEvnetListener);
}
void InputManager::removeKeyEvnetListener(std::function<void(KeyboardEvent)> keyboardEvnetListener) {
    this->_keyEventListener.erase(keyboardEvnetListener);
}
void InputManager::removeMouseEvnetListener(std::function<void(MouseEvent)> mouseEvnetListener) {
    this->_mouseEventListener.erase(mouseEvnetListener);
}


}
