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
    for(int i=0;i< displayCount;++i) {
        CGRect monitor = CGDisplayBounds(onlineDisplays[i]);
        CGFloat height = CGRectGetHeight(monitor);
        CGFloat width = CGRectGetWidth(monitor);
        Log::i(TAG, std::string("w ").append(std::to_string(width)).append(" h ").append(std::to_string(height)));
    }
#endif
}

}
