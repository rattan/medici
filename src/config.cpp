#include "config.h"

void Config::clear() {
    appVersion = DEFAULT_APP_VERSION;
    protocolVersion = DEFAULT_PROTOCOL_VERSION;
    name.clear();
    uuid.clear();
    ipAddress.clear();
    displays.clear();
    connections.clear();
}

std::string Config::toString() const {
    std::stringstream result;
    result<<"ME:\n"<<toStringMe();
    for(auto& config: connections) {
        result<<"OTHER:\n";
        result<<config.toStringMe();
    }
    return result.str();
}

std::string Config::toStringMe() const {
    std::stringstream result;
    result<<KEY_APP_VERSION<<"="<<appVersion<<"\n";
    result<<KEY_PROTOCOL_VERSION<<"="<<protocolVersion<<"\n";
    result<<KEY_NAME<<"="<<name<<"\n";
    result<<KEY_UUID<<"="<<uuid<<"\n";
    result<<KEY_IP_ADDRESS<<"="<<ipAddress<<"\n";
    for(auto display: displays) {
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
                this->connections.push_back(*target);
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
        this->connections.push_back(*target);
    }

    std::cout << toString() << std::endl;
}

void Config::assign(Config* const target, const std::string &key, const std::string &value)
{
    switch (keyHash(key.c_str()))
    {
    case keyHash(KEY_APP_VERSION):
        target->appVersion = std::stoi(value);
        break;
    case keyHash(KEY_PROTOCOL_VERSION):
        target->protocolVersion = std::stoi(value);
        break;
    case keyHash(KEY_NAME):
        target->name = value;
        break;
    case keyHash(KEY_UUID):
        target->uuid = value;
        break;
    case keyHash(KEY_IP_ADDRESS):
        target->ipAddress = value;
        break;
    case keyHash(KEY_DISPLAY):
        target->displays.push_back(Display(value));
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
