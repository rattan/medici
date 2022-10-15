#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "displaymanager.h"

namespace med {


class DisplayManagerWindows: public DisplayManager {
private:
    friend class DependencySet;
    DisplayManagerWindows();
    #ifdef _WIN32
        static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
    #endif
};

}
