#pragma once

#include <string>
#include <list>

class Config {
    int appVersion;
    int protocolVersion;
    std::string name;
    std::string uuid;
    
    std::list<Config> connections;
}
