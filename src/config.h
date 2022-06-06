#pragma once

#include "display.h"

#include <fstream>
#include <string>
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
    std::string name;
    std::string uuid;
    std::string ipAddress;
    std::list<Display> displays;
    
    std::list<Config> connections;
    
    void parse(const std::list<std::string> &configLines);
    void assign(const std::string &key, const std::string &value);

public:
    void load(const std::string from = DEFAULT_CONFIG_FILE);
    void save(const std::string to = DEFAULT_CONFIG_FILE) const;
};
