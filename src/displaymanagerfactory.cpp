#include "displaymanagerfactory.h"

namespace med {


const std::string DisplayManagerFactory::TAG = "DisplayManagerFactory";

DisplayManager& DisplayManagerFactory::instance() {
    static DisplayManager* i = nullptr;
    if(i == nullptr) {
        switch(PlatformManager::getHostOperatingSystem()) {
            case PlatformManager::OS::WINDOWS:
                i = new DisplayManagerWindows();
                break;
            case PlatformManager::OS::LINUX:
                i = new DisplayManagerLinux();
                break;
            case PlatformManager::OS::APPLE:
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
