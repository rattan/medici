#pragma once

#include "display.h"
#include "uuid.h"

#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <regex>
#include <iostream>
#include <functional>

#define DEFAULT_CONFIG_FILE ".config"

// keys
#define KEY_APP_VERSION "APP_VERSION"
#define KEY_PROTOCOL_VERSION "PROTOCOL_VERSION"
#define KEY_NAME "NAME"
#define KEY_UUID "UUID"
#define KEY_IP_ADDRESS "IP_ADDRESS"
#define KEY_DISPLAY "DISPLAY"

// default values
#define DEFAULT_APP_VERSION 0
#define DEFAULT_PROTOCOL_VERSION 0


class Config {
    int appVersion = DEFAULT_APP_VERSION;
    int protocolVersion = DEFAULT_PROTOCOL_VERSION;
    std::string _name;
    std::string _uuid;
    std::string _ipAddress;
    std::list<Display> _displays;
    
    std::list<Config> _connections;
    

    void clear();
    void parse(const std::list<std::string> &configLines);
    void assign(Config* const target, const std::string &key, const std::string &value);
    std::string toString() const;
    std::string toStringMe() const;
public:
    void load(const std::string from = DEFAULT_CONFIG_FILE);
    void save(const std::string to = DEFAULT_CONFIG_FILE) const;

    std::string name() const;
    std::string uuid();
    std::string ipAddress() const;
    const std::list<Display>& displays() const;
    const std::list<Config>& connections() const;
};
