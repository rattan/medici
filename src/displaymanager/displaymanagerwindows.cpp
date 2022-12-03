#include "displaymanagerwindows.h"

namespace med {


DisplayManagerWindows::DisplayManagerWindows() {
#ifdef _WIN32
    EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(this));
#endif
}

#ifdef _WIN32
BOOL CALLBACK DisplayManagerWindows::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
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
        _this->addHostDisplay(Display(Rect(devMode.dmPosition.y, devMode.dmPosition.x, cxPhysical, cyPhysical)));
    }
    return TRUE;
}
#endif

}
