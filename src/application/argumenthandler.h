#pragma once

#include <string>
#include <regex>
#include <list>
#include <iterator>
#include <exception>
#include <sstream>

#include "../configmanager/configmanager.h"
#include "../util/textutil.h"

// keys
#define KEY_CONFIG "config"

#define KEY_NAME "name"

namespace med {


class ArgumentHandler {
    std::list<std::string> _argv;
    void parse();
    void consumeConfig(std::list<std::string>::iterator&it);
    
    void throwInvalidArgument(std::list<std::string>::iterator &it);
public:
    ArgumentHandler(int argc, char* argv[]);
    
    void printHelp();
};

}
