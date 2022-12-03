#pragma once

#include "jsondata.h"
#include "display.h"
#include "uuid.h"
#include "../util/log.h"
#include "../data/json.hpp"
#include "../platformmanager/platformmanager.h"

#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <regex>
#include <iostream>
#include <functional>
#include <type_traits>


// keys
#define JSON_PROPERTY_APP_VERSION "app_version"
#define JSON_PROPERTY_PROTOCOL_VERSION "protocol_version"
#define JSON_PROPERTY_OPERATING_SYSTEM "operating_system"
#define JSON_PROPERTY_NAME "name"
#define JSON_PROPERTY_UUID "uuid"
#define JSON_PROPERTY_IP_ADDRESS "ip_address"
#define JSON_PROPERTY_DISPLAYS "displays"

// default values
#define DEFAULT_APP_VERSION 0
#define DEFAULT_PROTOCOL_VERSION 0

namespace med {

class Config: public JsonData {
private:
    friend class ConfigManager;
    int _appVersion = DEFAULT_APP_VERSION;
    int _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    PlatformManager::OS _operatingSystem = PlatformManager::OS::NIL;
    Uuid _uuid;
    std::string _name;
    std::string _ipAddress;
    Display _display;

    Config(int appVersion = DEFAULT_APP_VERSION, int protocolVersion = DEFAULT_PROTOCOL_VERSION,
           PlatformManager::OS operatingSystem = PlatformManager::OS::NIL, std::string name = "",
           Uuid uuid = Uuid::gen(Uuid::version::FOUR), std::string ipAddress = "0.0.0.0",
           Display display = Display());
    void clear();
    virtual void setJson(nlohmann::json json);
public:
    virtual const nlohmann::json toJson() const;
    virtual const std::string tag() const;
    virtual Index packetIndex() const;
    
    int appVersion() const;
    int protocolVersion() const;
    PlatformManager::OS operatingSystem() const;
    std::string name() const;
    Uuid uuid() const;
    std::string ipAddress() const;
    const Display& display() const;
};

}
