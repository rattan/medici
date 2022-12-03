#include "dependencyset.h"

namespace med {

const std::string DependencySet::TAG = "DependencySet";

DisplayManager& DependencySet::getDisplayManager() {
    static DisplayManager* displayManager = nullptr;
    if(displayManager == nullptr) {
        switch(PlatformManager::getHostOperatingSystem()) {
            case PlatformManager::OS::WINDOWS:
                displayManager = new DisplayManagerWindows();
                break;
            case PlatformManager::OS::LINUX:
                displayManager = new DisplayManagerLinux();
                break;
            case PlatformManager::OS::APPLE:
                displayManager = new DisplayManagerApple();
                break;
            default:
                Log::e(TAG, "Ths operating system not support medici.");
            break;
        }
    }
    return *displayManager;
}

InputManager& DependencySet::getInputManager() {
    static InputManager* inputManager = nullptr;
    if(inputManager == nullptr) {
        switch(PlatformManager::getHostOperatingSystem()) {
            case PlatformManager::OS::WINDOWS:
                inputManager = new InputManagerWindows();
                break;
            case PlatformManager::OS::LINUX:
                inputManager = new InputManagerLinux();
                break;
            case PlatformManager::OS::APPLE:
                inputManager = new InputManagerApple();
                break;
            default:
                Log::e(TAG, "Ths operating system not support medici.");
            break;
        }
    }
    return *inputManager;
}
 
ConnectionManager& DependencySet::getConnectionManager() {
    static ConnectionManager* connectionManager = new ConnectionManager();
    return *connectionManager;
}

ServerManager& DependencySet::getServerManager() {
    static ServerManager* serverManager = new ServerManager();
    return *serverManager;
}

StateManager& DependencySet::getStateManger() {
    static StateManager* stateManager = new StateManager();
    return *stateManager;
}

}
