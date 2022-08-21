#include "log.h"

namespace med {

const std::string Log::TAG = "LOG";

Log& Log::instance() {
    static Log i;
    return i;
}

Log::Log() {
    this->consumeBuffer = true;
    this->consumeThread = std::thread(logBufferConsumer);
    
}

Log::~Log() {
    v(TAG, "Logger terminated.");
    this->consumeBuffer = false;
    this->consumeThread.join();
}

void Log::printLog(Log::Level lv, std::string tag, std::string message)  {
    std::stringstream logStream;
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    static pid_t pid = syscall(SYS_getpid);
    auto tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
    char logLevelChar = 'V';
    switch(lv) {
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

void Log::logBufferConsumer()  {
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

}
