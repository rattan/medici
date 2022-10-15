#pragma once

#include "displaymanager.h"
#include "../util/log.h"

#ifdef __APPLE__
#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>
#endif

namespace med {


class DisplayManagerApple: public DisplayManager {
private:
    friend class DependencySet;
    DisplayManagerApple();
    void updateHostDisplay();
};

}
