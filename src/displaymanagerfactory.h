#pragma once

#include <string>

#include "displaymanagerapple.h"
#include "displaymanagerlinux.h"
#include "displaymanagerwindows.h"
#include "configmanager.h"
#include "config.h"
#include "log.h"

namespace med {


class DisplayManagerFactory {
private:
    static const std::string TAG;
public:
    static DisplayManager& create();
};

}
