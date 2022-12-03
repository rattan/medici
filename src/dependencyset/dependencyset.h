#pragma once

#include <string>

#include "../displaymanager/displaymanagerapple.h"
#include "../displaymanager/displaymanagerlinux.h"
#include "../displaymanager/displaymanagerwindows.h"
#include "../platformmanager/platformmanager.h"
#include "../inputmanager/inputmanager.h"
#include "../inputmanager/inputmanagerapple.h"
#include "../inputmanager/inputmanagerlinux.h"
#include "../inputmanager/inputmanagerwindows.h"
#include "../connectionmanager/connectionmanager.h"
#include "../servermanager/servermanager.h"
#include "../statemanager/statemanager.h"
#include "../util/log.h"

namespace med {


class DependencySet {
private:
    static const std::string TAG;
public:
    static DisplayManager& getDisplayManager();
    static InputManager& getInputManager();
    static ConnectionManager& getConnectionManager();
    static ServerManager& getServerManager();
    static StateManager& getStateManger();
};

}
