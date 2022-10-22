#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <thread>
#include <queue>

#include <unistd.h>

// #include <sys/syscall.h>
#include <cctype>
#include <sys/types.h>

#define LOG_FILE "m.log"

namespace med {

class Log {
private:
    static Log& instance();
    Log();
    ~Log();
    
    enum class Level {
        VERBOSE = 0, DEBUGG = 1, INFO = 2, WARN = 3, _ERROR = 4
    } logLevel;
    std::queue<std::string> printBuffer;
    std::queue<std::string> fileBuffer;
    std::thread consumeThread;
    bool consumeBuffer;
    
    void printLog(Level lv, std::string tag, std::string message);
    
    static void logBufferConsumer();
    

    
public:
    static void v(std::string tag, std::string message) {
        instance().printLog(Level::VERBOSE, tag, message);
    }
    static void d(std::string tag, std::string message) {
        instance().printLog(Level::DEBUGG, tag, message);
    }
    static void i(std::string tag, std::string message) {
        instance().printLog(Level::INFO, tag, message);
    }
    static void w(std::string tag, std::string message) {
        instance().printLog(Level::WARN, tag, message);
    }
    static void e(std::string tag, std::string message) {
        instance().printLog(Level::_ERROR, tag, message);
    }
    
    static void setLegLevel(Level level) {
        instance().logLevel = level;
    }
    static Level getLogLevel() {
        return instance().logLevel;
    }
};

}
