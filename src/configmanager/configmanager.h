#pragma once

#include <map>
#include <list>
#include <sstream>
#include <string>
#include <regex>
#include <algorithm>

#include "../data/json.hpp"
#include "../data/config.h"
#include "../data/uuid.h"
#include "../util/log.h"
#include "../dependencyset/dependencyset.h"
#include "../platformmanager/platformmanager.h"

#define DEFAULT_CONFIG_FILE "config.json"

#define JSON_PROPERTY_HOST "host"
#define JSON_PROPERTY_CONNECTIONS "connections"


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
    const Config connection(Uuid uuid) const;
    
};

}
