#include "displaymanagerfactory.h"

namespace med {


const std::string DisplayManagerFactory::TAG = "DisplayManagerFactory";

DisplayManager& DisplayManagerFactory::create() {
    static DisplayManager* i = nullptr;
    if(i == nullptr) {
        const Config &config = ConfigManager::instance().hostConfig();
        switch(config.operatingSystem()) {
            case Config::OS::WINDOWS:
                i = new DisplayManagerWindows();
                break;
            case Config::OS::LINUX:
                i = new DisplayManagerLinux();
                break;
            case Config::OS::APPLE:
                i = new DisplayManagerApple();
                break;
            default:
                Log::e(TAG, "Ths operating system not support medici.");
            break;
        }
    }
    return *i;
}

}
