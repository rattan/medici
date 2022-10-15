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

std::string PlatformManager::getOperatingSystemString(OS operatingSystem) {
    return std::string(_osString[static_cast<int>(operatingSystem)]);
}

PlatformManager::OS PlatformManager::parseOs(const std::string &osString) {
    switch(TextUtil::hash(osString.c_str())) {
        case TextUtil::hash(OS_APPLE):
            return OS::APPLE;
        case TextUtil::hash(OS_LINUX):
            return OS::LINUX;
        case TextUtil::hash(OS_WINDOWS):
            return OS::WINDOWS;
        default:
            return OS::NIL;
    }
}

}
