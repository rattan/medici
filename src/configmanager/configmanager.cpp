#include "configmanager.h"

namespace med {


const std::string ConfigManager::TAG = "ConfigManager";

ConfigManager::ConfigManager(){
    load();
}

ConfigManager& ConfigManager::instance() {
    static ConfigManager i;
    return i;
}

std::string ConfigManager::toString() const{
    nlohmann::json connections = nlohmann::json::array();
    for(const auto &connection: _connections) {
        connections.push_back(connection.second.toJson());
    }
    return nlohmann::json({
        {JSON_PROPERTY_HOST, _hostConfig.toJson()},
        {JSON_PROPERTY_CONNECTIONS, connections}
    }).dump(4);
}

const Config& ConfigManager::getDefaultConfig() const{
    static Config defaultConfig;
    return defaultConfig;
}

const Config ConfigManager::getDefaultHostConfig() const{
    Config hostDefaultConfig(DEFAULT_APP_VERSION, DEFAULT_PROTOCOL_VERSION, PlatformManager::getHostOperatingSystem(),
                             TcpSocket::hostName(), Uuid::gen(Uuid::version::FOUR), TcpSocket::hostIp(),
                             DependencySet::getDisplayManager().getHostDisplays());
    if(hostDefaultConfig.operatingSystem() == PlatformManager::OS::NIL) {
        Log::e(TAG, "This operating system not support medici.");
    }
    return hostDefaultConfig;
}

void ConfigManager::load(const std::string from)
{
    std::ifstream fin(from);
    try{
        nlohmann::json configJson = nlohmann::json::parse(fin);
        _hostConfig.setJson(configJson[JSON_PROPERTY_HOST]);
        _connections.clear();
        nlohmann::json connectionsJson = configJson[JSON_PROPERTY_CONNECTIONS];
        for(const auto& connection: connectionsJson) {
            Config config;
            config.setJson(connection);
            // _connections[config.uuid()] = config;
            _connections.insert(std::pair<Uuid, Config>(config.uuid(), config));
        }
    } catch(nlohmann::detail::parse_error e) {
        Log::e(TAG, std::string(e.what()) + "make default configure.");
        _hostConfig = getDefaultHostConfig();
        _connections.clear();
    }
    this->validateHostConfig();
    Log::i(TAG, std::string("Config loaded. Host configuration: ").append(hostConfig().toString()));
}

void ConfigManager::validateHostConfig() {
    Config current = getDefaultHostConfig();
    
    if (this->_hostConfig.operatingSystem() != current.operatingSystem()) {
        this->_hostConfig._operatingSystem = current._operatingSystem;
    }
    if (this->_hostConfig.ipAddress() != current.ipAddress()) {
        this->_hostConfig._ipAddress = current.ipAddress();
    }
    this->_hostConfig._display = current.display();
}

void ConfigManager::save(const std::string to) const
{
    std::ofstream fout;
    fout.open(to);
    fout<<toString();
    fout.close();
}

void ConfigManager::setHostName(const std::string& name) {
    this->_hostConfig._name = name;
}
const Config& ConfigManager::hostConfig() const {
    return this->_hostConfig;
}
std::list<Config> ConfigManager::connections() const {
    std::list<Config> result;
    std::transform(this->_connections.begin(), this->_connections.end(), std::back_inserter(result), [](const std::pair<Uuid, Config> &p){return p.second;});
    return result;
}

const Config ConfigManager::connection(Uuid uuid) const {
    return this->_connections.at(uuid);
}

}
