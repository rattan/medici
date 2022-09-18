#pragma once

#include "inputmanager.h"

#ifdef _WIN32
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
