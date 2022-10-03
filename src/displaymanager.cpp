#include "displaymanager.h"

namespace med {


const std::string DisplayManager::TAG = "DisplayManager";

DisplayManager::DisplayManager() {
}

const std::list<Display> DisplayManager::getHostDisplays() {
    return this->_hostDisplays;
}

void DisplayManager::addHostDisplayChangeListener(std::function<void(std::list<Display>)> &displayChangeListener) {
    this->_displayChangeListener.push_back(displayChangeListener);
}

//void DisplayManager::removeHostDisplyaChangeListener(std::function<void(std::list<Display>)> &displayChangeListener) {
//    this->_displayChangeListener.remove(displayChangeListener);
//}

void DisplayManager::addHostDisplay(Display display) {
    this->_hostDisplays.push_back(display);
}

}

