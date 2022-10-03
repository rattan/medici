#pragma once

#include "inputmanager.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace med {

class InputManagerWindows: public InputManager {
    friend class DependencySet;
    static const std::string TAG;
    
    void start() override;
    void stop() override;
    
};

}
