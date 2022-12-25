#include "application.h"

namespace med {

const std::string Application::TAG = "Medici Application";
int Application::instanceCount = 0;

Application::Application(int argc, char* argv[]): argumentCount(argc), argumentValue(argv) {
    ++instanceCount;
    if(instanceCount > 1) {
        Log::w(TAG, "Multiple application instance " + std::to_string(instanceCount));
    }
}

Application::~Application() {
    --instanceCount;
    if(instanceCount == 0) {
        ConfigManager::instance().save();
    }
    auto &serverManager = DependencySet::getServerManager();
    serverManager.stopBroadCastingServer();
    serverManager.stopMediciConnectionServer();
    
    Log::i(TAG, "----- terminate medici application. -----");
}

int Application::exec() {
    if(executing) {
        Log::w(TAG, "application already executing");
        return 0;
    }
    executing = true;
    Log::i(TAG, "-----   start medici application.   -----");
    auto &configManager = ConfigManager::instance();
    auto &serverManager = DependencySet::getServerManager();
    auto &connectionManager = DependencySet::getConnectionManager();
    serverManager.startMediciConnectionServer([&](TcpSocket socket) {
        connectionManager.addConnection(std::move(socket));
    });
    serverManager.startBroadcastingServer([&](TcpSocket socket) {
        connectionManager.addBroadCastConnection(std::move(socket));
    });

    auto &inputManager = DependencySet::getInputManager();
    auto &stateManager = DependencySet::getStateManager();
    stateManager.setConnections(configManager.connections());
    inputManager.addKeyEvnetListener([&](KeyboardEvent kEvent) {
        Uuid target = stateManager.getFocused();
        if (ConfigManager::instance().hostConfig().uuid() == target) {
            // flush event to host
        } else {
            connectionManager.send(target, kEvent);
        }
    });
    inputManager.addMouseEvnetListener([&](MouseEvent mEvent) {
        stateManager.moveGlobalPosition(mEvent.moveXY());
        Uuid target = stateManager.getFocused();
        if (ConfigManager::instance().hostConfig().uuid() == target) {
            // flush event to host
        } else {
            connectionManager.send(target, mEvent);
        }
    });

    // run keyboard, mouse input loop and block before application end.
    inputManager.start();

    return 0;
}
}
