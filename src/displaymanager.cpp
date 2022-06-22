#include "displaymanager.h"

#ifdef _WIN32
BOOL CALLBACK DisplayManager::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
    DisplayManager* _this = reinterpret_cast<DisplayManager*>(dwData);
    MONITORINFOEX monitorInfoEx;
    monitorInfoEx.cbSize = sizeof(monitorInfoEx);
    if (GetMonitorInfo(hMonitor, &monitorInfoEx)) {
        // monitorInfoEx.cbSize = sizeof(monitorInfoEx);
        // GetMonitorInfo(hMonitor, &monitorInfoEx);
        // auto cxLogical = monitorInfoEx.rcMonitor.right - monitorInfoEx.rcMonitor.left;
        // auto cyLogical = monitorInfoEx.rcMonitor.bottom - monitorInfoEx.rcMonitor.top;

        DEVMODE devMode;
        devMode.dmSize = sizeof(devMode);
        devMode.dmDriverExtra = 0;
        EnumDisplaySettings(monitorInfoEx.szDevice, ENUM_CURRENT_SETTINGS, &devMode);
        auto cxPhysical = devMode.dmPelsWidth;
        auto cyPhysical = devMode.dmPelsHeight;

        // auto horizontalScale = ((double)cxPhysical / (double)cxLogical);
        // auto verticalScale = ((double)cyPhysical / (double)cyLogical);
        _this->_hostDisplays.push_back(Display(Rect(devMode.dmPosition.y, devMode.dmPosition.x, cxPhysical, cyPhysical)));
    }
    return TRUE;
}
#endif

void DisplayManager::updateHostDisplays() {
    // this->_hostUuid = Config::instance().uuid();
    this->_hostDisplays.clear();
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(this));

    for(auto d: this->_hostDisplays) {
        std::cout<<d.toString()<<std::endl;
    }
}

void DisplayManager::magnetDisplay(std::string uuid) {

}

void DisplayManager::addDisplays(std::string uuid, std::list<Display> displays) {
    this->_otherDisplays.insert_or_assign(uuid, displays);
}

void DisplayManager::removeDisplays(std::string uuid) {
    this->_otherDisplays.erase(uuid);
}