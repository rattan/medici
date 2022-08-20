#pragma once

#include "data.h"
#include "display.h"
#include "uuid.h"
#include "textutil.h"
#include "tcpsocket.h"

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
#define KEY_NAME "name"
#define KEY_UUID "uuid"
#define KEY_IP_ADDRESS "ip_address"
#define KEY_DISPLAY "display"

// default values
#define DEFAULT_APP_VERSION 0
#define DEFAULT_PROTOCOL_VERSION 0


class Config: public Data {
    friend class ConfigManager;
    int _appVersion = DEFAULT_APP_VERSION;
    int _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    std::string _name;
    Uuid _uuid;
    std::string _ipAddress;
    std::list<Display> _displays;
    
    Config();
    
    void clear();
    void initDefaultHost();
    void initDefaultData();



public:
    static Config& instance();
    
    virtual std::string toString() const;
    virtual std::string tag() const;
    
    int appVersion() const;
    int protocolVersion() const;
    std::string name() const;
    Uuid uuid() const;
    std::string ipAddress() const;
    const std::list<Display>& displays() const;
};
