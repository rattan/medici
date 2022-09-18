#pragma once

#include <map>
#include <list>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>

#include "config.h"
#include "uuid.h"
#include "log.h"
#include "dependencyset.h"
#include "platformmanager.h"

#define DEFAULT_CONFIG_FILE "m.config"

namespace med {


class ConfigManager {
private:
    static const std::string TAG;
    bool loaded = false;
    Config _hostConfig;
    std::map<Uuid, Config> _connections;
    
    
    ConfigManager();
    ConfigManager(const ConfigManager& o) = delete;
    ConfigManager(ConfigManager&& o) = delete;
    
    void load(const std::string from = DEFAULT_CONFIG_FILE);
    void assign(Config* const target, const std::string &key, const std::string &value);
    void parse(const std::list<std::string> &configLines);
    void validateHostConfig();
    
    
    const Config& getDefaultConfig() const;
    const Config getDefaultHostConfig() const;
    
    std::string toString() const;
    
    
public:
    static ConfigManager& instance();

    void save(const std::string to = DEFAULT_CONFIG_FILE) const;
    void setHostName(const std::string& name);
    const Config& hostConfig() const;
    std::list<Config> connections() const;
    
};

}
