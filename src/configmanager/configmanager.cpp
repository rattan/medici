#include "configmanager.h"

namespace med {


const std::string ConfigManager::TAG = "ConfigManager";

ConfigManager::ConfigManager(){}

ConfigManager& ConfigManager::instance() {
    static ConfigManager i;
    if(!i.loaded) {
        i.load();
        i.loaded = true;
    }
    return i;
}

std::string ConfigManager::toString() const{
    std::stringstream stringBuilder;
    stringBuilder<<"HOST:"<<std::endl;
    stringBuilder<<_hostConfig.toString();
    for(auto& connection: connections()) {
        stringBuilder<<"CONNECTION:"<<std::endl;
        stringBuilder<<connection.toString();
    }
    return stringBuilder.str();
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
        _hostConfig = getDefaultHostConfig();
    } else {
        parse(configList);
    }
    
    this->validateHostConfig();
    Log::i(TAG, std::string("New config loaded. Host configuration: ").append(hostConfig().toString()));
}

void ConfigManager::parse(const std::list<std::string> &configLines)
{
    Config other;
    Config *target = &_hostConfig;
    
    for (auto& line : configLines)
    {
        if(std::regex_match(line, std::regex(R"((HOST|CONNECTION):)"))) {
            if(target == &other) {
                this->_connections.insert(std::pair<Uuid, Config>(target->uuid(), *target));
            }

            switch (TextUtil::hash(line.c_str()))
            {
            case TextUtil::hash("HOST:"):
                    target = &_hostConfig;
                    *target = getDefaultHostConfig();
                break;
            case TextUtil::hash("CONNECTION:"):
                target = &other;
                    target->clear();
                break;
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
    if (target == &other) {
        this->_connections.insert(std::pair<Uuid, Config>(target->uuid(), *target));
    }
}

void ConfigManager::validateHostConfig() {
    Config current = getDefaultHostConfig();
    
    if (this->_hostConfig.operatingSystem() != current.operatingSystem()) {
        this->_hostConfig._operatingSystem = current._operatingSystem;
    }
    if (this->_hostConfig.ipAddress() != current.ipAddress()) {
        this->_hostConfig._ipAddress = current.ipAddress();
    }
    const std::list<Display> &currentDisplays = current.displays();
    if (this->_hostConfig.displays().size() != currentDisplays.size()) {
        this->_hostConfig._displays = currentDisplays;
    } else {
        auto hostIt = this->_hostConfig.displays().begin();
        auto currentIt = current.displays().begin();
        while(hostIt != this->hostConfig().displays().end() && currentIt != current.displays().end()) {
            if(hostIt->toString() != currentIt->toString()) {
                this->_hostConfig._displays = currentDisplays;
                break;
            }
            ++hostIt;
            ++currentIt;
        }
    }
}

void ConfigManager::assign(Config* const target, const std::string &key, const std::string &value)
{
    switch (TextUtil::hash(key.c_str()))
    {
    case TextUtil::hash(KEY_APP_VERSION):
        target->_appVersion = std::stoi(value);
        break;
    case TextUtil::hash(KEY_PROTOCOL_VERSION):
        target->_protocolVersion = std::stoi(value);
        break;
    case TextUtil::hash(KEY_OPERATING_SYSTEM):
        switch(TextUtil::hash(value.c_str())) {
            case TextUtil::hash(OS_WINDOWS):
                target->_operatingSystem = PlatformManager::OS::WINDOWS;
                break;
            case TextUtil::hash(OS_APPLE):
                target->_operatingSystem = PlatformManager::OS::APPLE;
                break;
            case TextUtil::hash(OS_LINUX):
                target->_operatingSystem = PlatformManager::OS::LINUX;
                break;
            default:
                target->_operatingSystem = PlatformManager::OS::NIL;
        }
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
            Log::e(TAG, std::string("[").append(key).append("] is not valid key. "));
    }
}

void ConfigManager::save(const std::string to) const
{
    std::ofstream fout;
    std::string result = toString();
    fout.open(to);
    fout<<result;
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

}
