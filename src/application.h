#pragma once

#include <string>

#include "servermanager.h"
#include "connectionmanager.h"
#include "configmanager.h"
#include "log.h"

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
    
    ServerManager serverManager;
    ConnectionManager connectionManager;
    
public:
    Application(int argc, char* argv[]);
    ~Application();
    
    int exec();
};

}
