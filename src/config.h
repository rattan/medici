#pragma once

#include "data.h"
#include "display.h"
#include "uuid.h"
#include "textutil.h"
#include "tcpsocket.h"
#include "log.h"

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
#define OS_NIL "NIL"
#define OS_APPLE "APPLE"
#define OS_LINUX "LINUX"
#define OS_WINDOWS "WINDOWS"



namespace med {



class Config: public Data {
public:
    enum class OS: int {
        NIL = 0, APPLE, LINUX, WINDOWS
    };
    static const char *_osString[];

private:
    friend class ConfigManager;
    int _appVersion = DEFAULT_APP_VERSION;
    int _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    OS _operatingSystem = OS::NIL;
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
    
    virtual const std::string toString() const;
    virtual const std::string tag() const;
    
    int appVersion() const;
    int protocolVersion() const;
    OS operatingSystem() const;
    std::string osToString() const;
    std::string name() const;
    Uuid uuid() const;
    std::string ipAddress() const;
    const std::list<Display>& displays() const;
};

}
