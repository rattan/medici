#pragma once

#include <string>
#include <thread>
#include <functional>
#include <set>

#include "log.h"
#include "keyboardevent.h"
#include "mouseevent.h"

namespace med {

class InputManager {
    static const std::string TAG;
    std::set<std::function<void(KeyboardEvent)>> _keyEventListener;
    std::set<std::function<void(MouseEvent)>> _mouseEventListener;
    
protected:
    virtual void start() = 0;
    virtual void stop() = 0;
    
public:
    InputManager();
    ~InputManager();
    virtual void sendKeyEvent(KeyboardEvent keyEvent) final;
    virtual void sendMouseEvent(MouseEvent mouseEvent) final;
    virtual void addKeyEvnetListener(std::function<void(KeyboardEvent)> keyboardEvnetListener) final;
    virtual void addMouseEvnetListener(std::function<void(MouseEvent)> mouseEvnetListener) final;
    virtual void removeKeyEvnetListener(std::function<void(KeyboardEvent)> keyboardEvnetListener) final;
    virtual void removeMouseEvnetListener(std::function<void(MouseEvent)> mouseEvnetListener) final;
};

}
