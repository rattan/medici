#include "log.h"

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
