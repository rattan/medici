#include "argumenthandler.h"

ArgumentHandler::ArgumentHandler(int argc, char *argv[]) {
    for(int i=0; i < argc; ++i) {
        this->_argv.push_back(argv[i]);
    }
    this->parse();
}

void ArgumentHandler::parse() {
    auto it = this->_argv.begin();
    while(it!= this->_argv.end()) {
        switch(TextUtil::hash(it->c_str())) {
            case TextUtil::hash(KEY_CONFIG):
                consumeConfig(++it);
                break;
            default:
                std::stringstream errorMessage;
                errorMessage<<"invalid argument: "<<*it;
                throw std::runtime_error(errorMessage.str());
        }
    }
}

void ArgumentHandler::consumeConfig(std::__list_iterator<std::string, void*> it) {
    if(it != this->_argv.end()) {
        std::smatch match;
//        if(std::regex_match(*it, match, std::regex(R"((name|)=(.*))"))) {
//            switch(
//        }
    }
    
}

void ArgumentHandler::printHelp() {
    
}

