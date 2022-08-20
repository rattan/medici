#include "config.h"

Config::Config() {
}

void Config::clear() {
    _appVersion = DEFAULT_APP_VERSION;
    _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    _name.clear();
    _uuid = Uuid::gen(Uuid::version::NIL);
    _ipAddress.clear();
    _displays.clear();
}

void Config::initDefaultHost() {
    this->_name = TcpSocket::hostName();
    this->_uuid = Uuid::gen(Uuid::version::FOUR);
    this->_ipAddress = TcpSocket::hostIp();
    this->_displays.clear();
}

void Config::initDefaultData() {
    this->_name.clear();
    this->_uuid = Uuid::gen(Uuid::version::FOUR);
    this->_ipAddress = "0.0.0.0";
    this->_displays.clear();
}

std::string Config::toString() const {
    std::stringstream result;
    result<<KEY_APP_VERSION<<"="<<appVersion()<<std::endl;
    result<<KEY_PROTOCOL_VERSION<<"="<<protocolVersion()<<std::endl;
    result<<KEY_NAME<<"="<<name()<<std::endl;
    result<<KEY_UUID<<"="<<uuid().toString()<<std::endl;
    result<<KEY_IP_ADDRESS<<"="<<ipAddress()<<std::endl;
    for(auto display: _displays) {
        result<<KEY_DISPLAY<<"="<< display.toString() << std::endl;
    }
    return result.str();
}

std::string Config::tag() const{
    return "Config";
}

int Config::appVersion() const {
    return this->_appVersion;
}
int Config::protocolVersion() const {
    return this->_protocolVersion;
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
