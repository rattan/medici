#pragma once

#include <string>

#define OS_NIL "NIL"
#define OS_APPLE "APPLE"
#define OS_LINUX "LINUX"
#define OS_WINDOWS "WINDOWS"

namespace med {

class PlatformManager {
public:
    enum class OS: int {
        NIL = 0, APPLE, LINUX, WINDOWS
    };
private:
    static const char *_osString[];
public:
    static OS getHostOperatingSystem();
    static std::string getHostOperatingSystemString(OS operatingSystem = getHostOperatingSystem());
};

}
