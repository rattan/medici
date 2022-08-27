#include "config.h"

namespace med {

Config::Config(int appVersion, int protocolVersion, PlatformManager::OS operatingSystem, std::string name,
                   Uuid uuid, std::string ipAddress, std::list<Display> displays):
    _appVersion(appVersion), _protocolVersion(protocolVersion), _operatingSystem(operatingSystem), _name(name),
    _uuid(uuid), _ipAddress(ipAddress), _displays(displays) {}

void Config::clear() {
    new (this)Config();
}

const std::string Config::toString() const {
    std::stringstream result;
    result<<KEY_APP_VERSION<<"="<<appVersion()<<std::endl;
    result<<KEY_PROTOCOL_VERSION<<"="<<protocolVersion()<<std::endl;
    result<<KEY_OPERATING_SYSTEM<<"="<<PlatformManager::getHostOperatingSystemString(operatingSystem())<<std::endl;
    result<<KEY_NAME<<"="<<name()<<std::endl;
    result<<KEY_UUID<<"="<<uuid().toString()<<std::endl;
    result<<KEY_IP_ADDRESS<<"="<<ipAddress()<<std::endl;
    for(auto display: _displays) {
        result<<KEY_DISPLAY<<"="<< display.toString() << std::endl;
    }
    return result.str();
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
