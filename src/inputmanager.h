#pragma once

#include <string>
#include <thread>
#include <functional>
#include <vector>

#include "log.h"
#include "keyboardevent.h"
#include "mouseevent.h"

namespace med {

class InputManager {

    std::vector<std::function<void(KeyboardEvent)>> _keyEventListener;
    std::vector<std::function<void(MouseEvent)>> _mouseEventListener;
    
    void startInternal();
    void stopInternal();

protected:
    static const std::string TAG;
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
