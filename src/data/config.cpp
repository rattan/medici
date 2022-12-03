#include "config.h"

namespace med {

Config::Config(int appVersion, int protocolVersion, PlatformManager::OS operatingSystem, std::string name,
                   Uuid uuid, std::string ipAddress, Display display):
    _appVersion(appVersion), _protocolVersion(protocolVersion), _operatingSystem(operatingSystem), _name(name),
    _uuid(uuid), _ipAddress(ipAddress), _display(display) {}

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
    _display = Display();
    _display.setJson(json[JSON_PROPERTY_DISPLAYS]);
    } catch(nlohmann::detail::type_error e) {
        Log::e(tag(), std::string(e.what()) + json.dump(4));
        clear();
    }
}

const nlohmann::json Config::toJson() const {
    return nlohmann::json({
        {JSON_PROPERTY_APP_VERSION, appVersion()},
        {JSON_PROPERTY_PROTOCOL_VERSION, protocolVersion()},
        {JSON_PROPERTY_OPERATING_SYSTEM, PlatformManager::getOperatingSystemString(operatingSystem())},
        {JSON_PROPERTY_NAME, name()},
        {JSON_PROPERTY_UUID, uuid().toString()},
        {JSON_PROPERTY_IP_ADDRESS, ipAddress()},
        {JSON_PROPERTY_DISPLAYS, display().toJson()}
    });
}

const std::string Config::tag() const{
    return "Config";
}

Packet::Index Config::packetIndex() const {
    return Index::CONFIG;
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
const Display& Config::display() const {
    return this->_display;
}

}
