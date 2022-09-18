#pragma once

#ifdef _WIN32
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
