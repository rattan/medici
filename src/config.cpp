#include "config.h"

Config::Config() {
}

Config::Config(std::true_type) {
    load();
}

Config::~Config() {
    save();
}

void Config::clear() {
    _appVersion = DEFAULT_APP_VERSION;
    _protocolVersion = DEFAULT_PROTOCOL_VERSION;
    _name.clear();
    _uuid.clear();
    _ipAddress.clear();
    _displays.clear();
    _connections.clear();
}

void Config::initDefaultHost() {
    this->_name = TcpSocket::hostName();
    this->_uuid = Uuid::gen();
    this->_ipAddress = TcpSocket::hostIp();
    this->_displays.clear();
    this->_connections.clear();
}

std::string Config::toString() const {
    std::stringstream result;
    result<<"HOST:\n"<<toStringMe();
    for(auto& config: _connections) {
        result<<"CONNECTION:\n";
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
    if(configList.empty()) {
        initDefaultHost();
    } else {
        parse(configList);
    }
}

void Config::parse(const std::list<std::string> &configLines)
{
    Config other;
    Config *target = this;
    clear();
    for (auto& line : configLines)
    {
        if(std::regex_match(line, std::regex(R"((HOST|CONNECTION):)"))) {
            if(target == &other) {
                this->_connections.push_back(*target);
            }
            switch (TextUtil::hash(line.c_str()))
            {
            case TextUtil::hash("HOST:"):
                target = this;
                break;
            case TextUtil::hash("CONNECTION:"):
                target = &other;
                break;
            }
            if(target == &other) {
                target->clear();
            } else if(target == this) {
                target->initDefaultHost();
            }
            continue;
        }

        std::regex re(R"((#)?(.*?)=(.*))");
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
}

void Config::assign(Config* const target, const std::string &key, const std::string &value)
{
    switch (TextUtil::hash(key.c_str()))
    {
    case TextUtil::hash(KEY_APP_VERSION):
        target->_appVersion = std::stoi(value);
        break;
    case TextUtil::hash(KEY_PROTOCOL_VERSION):
        target->_protocolVersion = std::stoi(value);
        break;
    case TextUtil::hash(KEY_NAME):
        target->_name = value;
        break;
    case TextUtil::hash(KEY_UUID):
        target->_uuid = value;
        break;
    case TextUtil::hash(KEY_IP_ADDRESS):
        target->_ipAddress = value;
        break;
    case TextUtil::hash(KEY_DISPLAY):
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

Config& Config::instance() {
    static Config i{ std::true_type() };
    return i;
}

void Config::setName(std::string &name) {
    this->_name = name;
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
