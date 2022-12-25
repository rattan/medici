#pragma once

#include <string>


#include "../dependencyset/dependencyset.h"
#include "../servermanager/servermanager.h"
#include "../inputmanager/inputmanager.h"
#include "../connectionmanager/connectionmanager.h"
#include "../configmanager/configmanager.h"
#include "../statemanager/statemanager.h"
#include "../util/log.h"

// This is Application class for Medici process.
// it'll be start, managing, destroy medici service.
// only using in main.cpp

namespace med {

class Application {
    static const std::string TAG;
    static int instanceCount;
    int argumentCount = 0;
    char** argumentValue = nullptr;
    bool executing = false;
    
public:
    Application(int argc, char* argv[]);
    ~Application();
    
    int exec();
};

}
