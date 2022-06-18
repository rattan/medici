#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#endif


#include <iostream>
#include <thread>

class InputHandler {

public:
    InputHandler();
};
