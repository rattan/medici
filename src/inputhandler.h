#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
//#include <Carbon/Carbon.h>
//#include <CoreFoundation/CoreFoundation.h>
//#include <ApplicationServices/ApplicationServices.h>
#endif


#include <iostream>
#include <thread>
#include <functional>

#include "keyboardevent.h"
#include "mouseevent.h"

class InputHandler {
    std::function<void(KeyboardEvent)> _keyEventListener;
    std::function<void(MouseEvent)> _mouseEventListener;
public:
    InputHandler(std::function<void(KeyboardEvent)> keyEvent, std::function<void(MouseEvent)> mouseEvent);
};
