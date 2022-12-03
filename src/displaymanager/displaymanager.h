#pragma once

#include <list>
#include <map>
#include <string>
#include <functional>

#include "../data/display.h"
#include "../data/uuid.h"
// #include "../data/config.h"

namespace med {


class DisplayManager {
protected:
    friend class DependencySet;
    static const std::string TAG;
    
    Display _hostDisplays;
    std::list<std::function<void(Display)>> _displayChangeListener;
    DisplayManager();
    

public:

    const Display getHostDisplays();
    void addHostDisplayChangeListener(std::function<void(Display)> &displayChangeListener);
//    void removeHostDisplyaChangeListener(std::function<void(std::list<Display>)> &displayChangeListener);
    void setHostDisplay(Display display);
};

}
