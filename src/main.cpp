#include "log.h"
#include "configmanager.h"


int main(int argc, char* argv[]) {
    Log::v("main", "-----   start medici process.   -----");
    ConfigManager& configManager = ConfigManager::instance();
    
    
    configManager.save();
    Log::v("main", "----- terminate medici process. -----");
    return 0;
}
