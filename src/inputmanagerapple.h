#pragma once

#include "inputmanager.h"

#ifdef __APPLE__
//#include <Carbon/Carbon.h>
//#include <CoreFoundation/CoreFoundation.h>
//#include <ApplicationServices/ApplicationServices.h>
#endif

namespace med {

class InputManagerApple: public InputManager {
    friend class DependencySet;
    static const std::string TAG;
    
    void start() override;
    void stop() override;
    
};

}
