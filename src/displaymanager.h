#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <list>
#include <map>
#include <string>
#include <iostream>

#include "display.h"
#include "uuid.h"
// #include "config.h"

class DisplayManager {
    const Uuid &_hostUuid;
    std::list<Display> _hostDisplays;
    std::map<Uuid, std::list<Display>> _otherDisplays;

#ifdef _WIN32
    static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
#endif

    public:
    DisplayManager();
    void updateHostDisplays();
    void magnetDisplay(const Uuid &uuid);
    void addDisplays(const Uuid &uuid, std::list<Display> displays);
    void removeDisplays(const Uuid &uuid);
};