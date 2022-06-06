#include "config.h"

void Config::load(const std::string from) {
    std::ifstream fin;
    fin.open(from);
    std::list<std::string> configList;
    std::string line;
    while(true) {
        fin>>line;
        if(fin) {
            configList.push_back(line);
        } else {
            break;
        }
    }
    fin.close();
    parse(configList);
}
void Config::parse(const std::list<std::string> &configLines) {
    std::regex re(R"((#)?(.*)=(.*))");
    for(auto line: configLines) {
        std::smatch match;
        if(std::regex_match(line, match, re)) {
            if(match[1].matched) {
                continue;
            }
            assign(match[2].str(), match[3].str());
        }
    }
    std::cout<<appVersion<<" "<<protocolVersion<<" "<<name<<" "<<uuid<<" "<<ipAddress<<std::endl;
    
}

constexpr unsigned long long keyHash(const char* key) {
    return key[0] ? static_cast<unsigned long long>(key[0]) + 0xEDB8832Full * keyHash(key + 1) : 8603;
}

void Config::assign(const std::string &key, const std::string &value) {
    switch(keyHash(key.c_str())) {
        case keyHash(KEY_APP_VERSION):
            this->appVersion = std::stoi(value);
            break;
        case keyHash(KEY_PROTOCOL_VERSION):
            this->protocolVersion = std::stoi(value);
            break;
        case keyHash(KEY_NAME):
            this->name = value;
            break;
        case keyHash(KEY_UUID):
            this->uuid = value;
            break;
        case keyHash(KEY_IP_ADDRESS):
            this->ipAddress = value;
            break;
        case keyHash(KEY_DISPLAY):
//            this->displays.push_back();
            break;
        default:
            std::cerr<<"["<<key<<"] is not valid key. "<<std::endl;
    }
}

void Config::save(const std::string to) const {
    
}
