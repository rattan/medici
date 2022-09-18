#pragma once

#include "inputmanager.h"

namespace med {

class InputManagerLinux: public InputManager {
    friend class DependencySet;
    
    void start() override;
    void stop() override;
    
};

}
