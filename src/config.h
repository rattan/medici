#pragma once

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

#define DEFAULT_CONFIG_FILE ".config"

// keys
#define KEY_APP_VERSION "app_version"
#define KEY_PROTOCOL_VERSION "protoco_version"
#define KEY_NAME "name"
#define KEY_UUID "uuid"
#define KEY_IP_ADDRESS "ip_address"
#define KEY_DISPLAY "display"

// default values
#define DEFAULT_APP_VERSION 0
#define DEFAULT_PROTOCOL_VERSION 0


class Config {
    int _appVersion = DEFAULT_APP_VERSION;
    int _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    std::string _name;
    std::string _uuid;
    std::string _ipAddress;
    std::list<Display> _displays;
    
    std::list<Config> _connections;
    
    Config();
    Config(std::true_type);
    
    void clear();
    void initDefaultHost();
    void parse(const std::list<std::string> &configLines);
    void assign(Config* const target, const std::string &key, const std::string &value);
    std::string toString() const;
    std::string toStringMe() const;
    void load(const std::string from = DEFAULT_CONFIG_FILE);
    void save(const std::string to = DEFAULT_CONFIG_FILE) const;

public:
    static Config& instance();
    ~Config();



    void setName(std::string& name);
    
    int appVersion() const;
    int protocolVersion() const;
    std::string name() const;
    std::string uuid() const;
    std::string ipAddress() const;
    const std::list<Display>& displays() const;
    const std::list<Config>& connections() const;
};
