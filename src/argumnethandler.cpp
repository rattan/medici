#include "argumenthandler.h"

ArgumentHandler::ArgumentHandler(int argc, char *argv[]) {
    for(int i=0; i < argc; ++i) {
        this->_argv.push_back(argv[i]);
    }
    this->parse();
}

void ArgumentHandler::parse() {
    auto it = this->_argv.begin();
    ++it;
    while(it!= this->_argv.end()) {
        switch(TextUtil::hash(it->c_str())) {
            case TextUtil::hash(KEY_CONFIG):
                consumeConfig(++it);
                break;
            default:
                throwInvalidArgument(it);
        }
    }
}

void ArgumentHandler::consumeConfig(std::__list_iterator<std::string, void*> &it) {
    Config &c = Config::instance();
    if(it != this->_argv.end()) {
        switch(TextUtil::hash(it->c_str())) {
            case TextUtil::hash(KEY_NAME):
                c.setName(*++it);
                break;
            default:
                throwInvalidArgument(it);
        }
    }
    ++it;
}

void ArgumentHandler::throwInvalidArgument(std::__list_iterator<std::string, void*> &it) {
    std::stringstream errorMessage;
    errorMessage<<"invalid argument: "<<*it;
    throw std::runtime_error(errorMessage.str());
}

void ArgumentHandler::printHelp() {
    
}

