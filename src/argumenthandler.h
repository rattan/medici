#pragma once

#include <string>
#include <regex>
#include <list>
#include <iterator>
#include <exception>
#include <sstream>

#include "config.h"
#include "textutil.h"

// keys
#define KEY_CONFIG "config"

class ArgumentHandler {
    std::list<std::string> _argv;
    void parse();
    void consumeConfig(std::__list_iterator<std::string, void*> it);
public:
    ArgumentHandler(int argc, char* argv[]);
    
    void printHelp();
};
