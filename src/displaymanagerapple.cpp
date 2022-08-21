#include "displaymanagerapple.h"


namespace med {


DisplayManagerApple::DisplayManagerApple() {
    this->updateHostDisplay();
}

void DisplayManagerApple::updateHostDisplay() {
#ifdef __APPLE__
    CGDirectDisplayID *onlineDisplays = new CGDirectDisplayID[99];
    uint32_t displayCount = 0;
    CGGetOnlineDisplayList(99, onlineDisplays, &displayCount);
    this->_hostDisplays.clear();
    for(int i = 0; i < displayCount; ++i) {
        CGRect monitor = CGDisplayBounds(onlineDisplays[i]);
        this->_hostDisplays.push_back(Display(Rect(monitor.origin.y, monitor.origin.x, monitor.size.width, monitor.size.height)));
    }
#endif
}

}
