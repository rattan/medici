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
    stringBuilder<<_config.toString();
    for(auto& connection: connections()) {
        stringBuilder<<"CONNECTION:"<<std::endl;
        stringBuilder<<connection.toString();
    }
    return stringBuilder.str();
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
        _config.initDefaultHost();
    } else {
        parse(configList);
    }
}

void ConfigManager::parse(const std::list<std::string> &configLines)
{
    Config other;
    Config *target = &_config;
    
    for (auto& line : configLines)
    {
        if(std::regex_match(line, std::regex(R"((HOST|CONNECTION):)"))) {
            if(target == &other) {
                this->_connections.insert(std::pair<Uuid, Config>(target->uuid(), *target));
            }

            switch (TextUtil::hash(line.c_str()))
            {
            case TextUtil::hash("HOST:"):
                    target = &_config;
                    target->initDefaultHost();
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
    if(target == &other) {
        this->_connections.insert(std::pair<Uuid, Config>(target->uuid(), *target));
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
                target->_operatingSystem = Config::OS::WINDOWS;
                break;
            case TextUtil::hash(OS_APPLE):
                target->_operatingSystem = Config::OS::APPLE;
                break;
            case TextUtil::hash(OS_LINUX):
                target->_operatingSystem = Config::OS::LINUX;
                break;
            default:
                target->_operatingSystem = Config::OS::NIL;
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
    this->_config._name = name;
}
const Config& ConfigManager::hostConfig() const {
    return this->_config;
}
std::list<Config> ConfigManager::connections() const {
    std::list<Config> result;
    std::transform(this->_connections.begin(), this->_connections.end(), std::back_inserter(result), [](const std::pair<Uuid, Config> &p){return p.second;});
    return result;
}

}
