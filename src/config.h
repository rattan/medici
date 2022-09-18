#pragma once

#include "data.h"
#include "display.h"
#include "uuid.h"
#include "textutil.h"
#include "tcpsocket.h"
#include "log.h"
#include "dependencyset.h"
#include "platformmanager.h"

#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <regex>
#include <iostream>
#include <functional>
#include <type_traits>


// keys
#define KEY_APP_VERSION "app_version"
#define KEY_PROTOCOL_VERSION "protocol_version"
#define KEY_OPERATING_SYSTEM "operating_system"
#define KEY_NAME "name"
#define KEY_UUID "uuid"
#define KEY_IP_ADDRESS "ip_address"
#define KEY_DISPLAY "display"

// default values
#define DEFAULT_APP_VERSION 0
#define DEFAULT_PROTOCOL_VERSION 0

namespace med {

class Config: public Data {
private:
    friend class ConfigManager;
    int _appVersion = DEFAULT_APP_VERSION;
    int _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    PlatformManager::OS _operatingSystem = PlatformManager::OS::NIL;
    Uuid _uuid;
    std::string _name;
    std::string _ipAddress;
    std::list<Display> _displays;

    Config(int appVersion = DEFAULT_APP_VERSION, int protocolVersion = DEFAULT_PROTOCOL_VERSION,
           PlatformManager::OS operatingSystem = PlatformManager::OS::NIL, std::string name = "",
           Uuid uuid = Uuid::gen(Uuid::version::FOUR), std::string ipAddress = "0.0.0.0",
           std::list<Display> displays = std::list<Display>());
    void clear();

public:
    
    virtual const std::string toString() const;
    virtual const std::string tag() const;
    
    int appVersion() const;
    int protocolVersion() const;
    PlatformManager::OS operatingSystem() const;
    std::string name() const;
    Uuid uuid() const;
    std::string ipAddress() const;
    const std::list<Display>& displays() const;
};

}
