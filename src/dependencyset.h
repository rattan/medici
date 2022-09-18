#pragma once

#include <string>

#include "displaymanagerapple.h"
#include "displaymanagerlinux.h"
#include "displaymanagerwindows.h"
#include "platformmanager.h"
#include "inputmanager.h"
#include "inputmanagerapple.h"
#include "inputmanagerlinux.h"
#include "inputmanagerwindows.h"
#include "connectionmanager.h"
#include "servermanager.h"
#include "log.h"

namespace med {


class DependencySet {
private:
    static const std::string TAG;
public:
    static DisplayManager& getDisplayManager();
    static InputManager& getInputManager();
    static ConnectionManager& getConnectionManager();
    static ServerManager& getServerManager();
};

}
