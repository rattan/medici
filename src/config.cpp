#include "config.h"

void Config::clear() {
    _appVersion = DEFAULT_APP_VERSION;
    _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    _name.clear();
    _uuid.clear();
    _ipAddress.clear();
    _displays.clear();
    _connections.clear();
}

std::string Config::toString() const {
    std::stringstream result;
    result<<"ME:\n"<<toStringMe();
    for(auto& config: _connections) {
        result<<"OTHER:\n";
        result<<config.toStringMe();
    }
    return result.str();
}

std::string Config::toStringMe() const {
    std::stringstream result;
    result<<KEY_APP_VERSION<<"="<<appVersion()<<"\n";
    result<<KEY_PROTOCOL_VERSION<<"="<<protocolVersion()<<"\n";
    result<<KEY_NAME<<"="<<name()<<"\n";
    result<<KEY_UUID<<"="<<uuid()<<"\n";
    result<<KEY_IP_ADDRESS<<"="<<ipAddress()<<"\n";
    for(auto display: _displays) {
        result<<KEY_DISPLAY<<"=" << display.toString() << "\n";
    }
    return result.str();
}

void Config::load(const std::string from)
{
    std::ifstream fin;
    fin.open(from);
    std::list<std::string> configList;
    std::string line;
    while (true)
    {
        std::getline(fin, line);
        if (fin)
        {
            configList.push_back(line);
        }
        else
        {
            break;
        }
    }
    fin.close();
    parse(configList);
}

constexpr unsigned long long keyHash(const char* key)
{
    return key[0] ? static_cast<unsigned long long>(key[0]) + 0xEDB8832Full * keyHash(key + 1) : 8603;
}

void Config::parse(const std::list<std::string> &configLines)
{
    Config other;
    Config *target = this;
    clear();
    for (auto& line : configLines)
    {
        if(std::regex_match(line, std::regex(R"((ME|OTHER):)"))) {
            if(target == &other) {
                this->_connections.push_back(*target);
            }
            switch (keyHash(line.c_str()))
            {
            case keyHash("ME:"):
                target = this;
                break;
            case keyHash("OTHER:"):
                target = &other;
                break;
            }
            target->clear();
            continue;
        }

        std::regex re(R"((#)?(.*)=(.*))");
        std::smatch match;
        if (std::regex_match(line, match, re))
        {
            if (match[1].matched)
            {
                continue;
            }
            assign(target, match[2].str(), match[3].str());
        }
    }
    if(target == &other) {
        this->_connections.push_back(*target);
    }

    std::cout << toString() << std::endl;
}

void Config::assign(Config* const target, const std::string &key, const std::string &value)
{
    switch (keyHash(key.c_str()))
    {
    case keyHash(KEY_APP_VERSION):
        target->_appVersion = std::stoi(value);
        break;
    case keyHash(KEY_PROTOCOL_VERSION):
        target->_protocolVersion = std::stoi(value);
        break;
    case keyHash(KEY_NAME):
        target->_name = value;
        break;
    case keyHash(KEY_UUID):
        target->_uuid = value;
        break;
    case keyHash(KEY_IP_ADDRESS):
        target->_ipAddress = value;
        break;
    case keyHash(KEY_DISPLAY):
        target->_displays.push_back(Display(value));
        break;
    default:
        std::cerr << "[" << key << "] is not valid key. " << std::endl;
    }
}

void Config::save(const std::string to) const
{    
    std::ofstream fout;
    std::string result = toString();
    fout.open(to);
    fout<<result;
    fout.close();
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
std::string Config::uuid() const {
    return this->_uuid;
}
std::string Config::ipAddress() const {
    return this->_ipAddress;
}
const std::list<Display>& Config::displays() const {
    return this->_displays;
}
const std::list<Config>& Config::connections() const {
    return this->_connections;
}