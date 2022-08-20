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
#include <sys/syscall.h>
#include <sys/types.h>

#define LOG_FILE "medici.log"

class Log {
private:
    static const std::string TAG;
    static Log& instance();
    Log();
    ~Log();
    
    enum class Level {
        VERBOSE = 0, DEBUGG = 1, INFO = 2, WARN = 3, ERROR = 4
    } logLevel;
    std::queue<std::string> printBuffer;
    std::queue<std::string> fileBuffer;
    std::thread consumeThread;
    bool consumeBuffer;
    
    void printLog(Level lv, std::string tag, std::string message) {
        std::stringstream logStream;
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        static pid_t pid = syscall(SYS_getpid);
        auto tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
        char logLevelChar = 'V';
        switch(logLevel) {
            case Level::VERBOSE:
                logLevelChar = 'V';
                break;
            case Level::DEBUGG:
                logLevelChar = 'D';
                break;
            case Level::INFO:
                logLevelChar = 'I';
                break;
            case Level::WARN:
                logLevelChar = 'W';
                break;
            case Level::ERROR:
                logLevelChar = 'E';
                break;
        }
        logStream<<std::put_time(std::localtime(&in_time_t), "%m-%d %X")<<' '<<pid<<'-'<<tid<<" ["<<logLevelChar<<"] "<<tag<<": "<<message;
        std::string logString = logStream.str();
        
        if(consumeBuffer) {
            if(logLevel <= lv) {
                printBuffer.push(logString);
            }
            fileBuffer.push(logString);
        }
    }
    
    static void logBufferConsumer() {
        v(TAG, "Logger start.");
        std::ofstream fout;
        Log& logInstance = instance();
        fout.open(LOG_FILE, std::ios_base::app);
        while(logInstance.consumeBuffer) {
            auto printSize = logInstance.printBuffer.size();
            for(int i = 0;i<printSize; ++i) {
                std::cout<<logInstance.printBuffer.front()<<std::endl;
                logInstance.printBuffer.pop();
            }
            printSize = logInstance.fileBuffer.size();
            for(int i = 0;i<printSize; ++i) {
                fout<<logInstance.fileBuffer.front()<<std::endl;
                logInstance.fileBuffer.pop();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        while(!logInstance.printBuffer.empty()) {
            std::cout<<logInstance.printBuffer.front()<<std::endl;
            logInstance.printBuffer.pop();
        }
        while(!logInstance.fileBuffer.empty()) {
            fout<<logInstance.fileBuffer.front()<<std::endl;
            logInstance.fileBuffer.pop();
        }
        fout.close();
    }
    

    
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
        instance().printLog(Level::ERROR, tag, message);
    }
    
    static void setLegLevel(Level level) {
        instance().logLevel = level;
    }
    static Level getLogLevel() {
        return instance().logLevel;
    }
};

