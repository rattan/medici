#include "platformmanager.h"

namespace med {

const char *PlatformManager::_osString[] = {
    OS_NIL, OS_APPLE, OS_LINUX, OS_WINDOWS
};

PlatformManager::OS PlatformManager::getHostOperatingSystem() {
    OS currentOS = OS::NIL;
#ifdef _WIN32
    currentOS = OS::WINDOWS;
#endif
#ifdef __linux__
    curentOS =  OS::LINUX;
#endif
#ifdef __APPLE__
    currentOS = OS::APPLE;
#endif
    return currentOS;
}

std::string PlatformManager::getHostOperatingSystemString(OS operatingSystem) {
    return std::string(_osString[static_cast<int>(operatingSystem)]);
}

}
