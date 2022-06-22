#pragma once

#ifdef _WIN32
#include <windows.h>
#endif

#include <list>
#include <map>
#include <string>
#include <iostream>

#include "display.h"
// #include "config.h"

class DisplayManager {
    std::string _hostUuid;
    std::list<Display> _hostDisplays;
    std::map<std::string, std::list<Display>> _otherDisplays;

#ifdef _WIN32
    static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
#endif

    public:
    void updateHostDisplays();
    void magnetDisplay(std::string uuid);
    void addDisplays(std::string uuid, std::list<Display> displays);
    void removeDisplays(std::string uuid);
};