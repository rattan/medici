#include "config.h"

namespace med {

Config::Config(int appVersion, int protocolVersion, PlatformManager::OS operatingSystem, std::string name,
                   Uuid uuid, std::string ipAddress, std::list<Display> displays):
    _appVersion(appVersion), _protocolVersion(protocolVersion), _operatingSystem(operatingSystem), _name(name),
    _uuid(uuid), _ipAddress(ipAddress), _displays(displays) {}

void Config::clear() {
    new (this)Config();
}

void Config::setJson(nlohmann::json json) {
    try {
    _appVersion = json[JSON_PROPERTY_APP_VERSION];
    _protocolVersion = json[JSON_PROPERTY_PROTOCOL_VERSION];
    _operatingSystem = PlatformManager::parseOs(json[JSON_PROPERTY_OPERATING_SYSTEM]);
    _uuid = Uuid(json[JSON_PROPERTY_UUID]);
    _name = json[JSON_PROPERTY_NAME];
    _ipAddress = json[JSON_PROPERTY_IP_ADDRESS];
    _displays.clear();
    for(const auto& displayJson: json[JSON_PROPERTY_DISPLAYS]) {
        Display display;
        display.setJson(displayJson);
        _displays.push_back(display);
    }
    } catch(nlohmann::detail::type_error e) {
        Log::e(tag(), std::string(e.what()) + json.dump(4));
        clear();
    }
}

const nlohmann::json Config::toJson() const {
    nlohmann::json jsonDisplays = nlohmann::json::array();
    for(const auto& display: displays()) {
        jsonDisplays.push_back(display.toJson());
    }
    return nlohmann::json({
        {JSON_PROPERTY_APP_VERSION, appVersion()},
        {JSON_PROPERTY_PROTOCOL_VERSION, protocolVersion()},
        {JSON_PROPERTY_OPERATING_SYSTEM, PlatformManager::getOperatingSystemString(operatingSystem())},
        {JSON_PROPERTY_NAME, name()},
        {JSON_PROPERTY_UUID, uuid().toString()},
        {JSON_PROPERTY_IP_ADDRESS, ipAddress()},
        {JSON_PROPERTY_DISPLAYS, jsonDisplays}
    });
}

const std::string Config::tag() const{
    return "Config";
}

int Config::appVersion() const {
    return this->_appVersion;
}
int Config::protocolVersion() const {
    return this->_protocolVersion;
}
PlatformManager::OS Config::operatingSystem() const{
    return this->_operatingSystem;
}
std::string Config::name() const {
    return this->_name;
}
Uuid Config::uuid() const {
    return this->_uuid;
}
std::string Config::ipAddress() const {
    return this->_ipAddress;
}
const std::list<Display>& Config::displays() const {
    return this->_displays;
}

}
