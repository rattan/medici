#include "log.h"
#include "configmanager.h"
#include "displaymanagerfactory.h"

using namespace med;

int main(int argc, char* argv[]) {
    Log::v("main", "-----   start medici process.   -----");
    ConfigManager& configManager = ConfigManager::instance();
    DisplayManagerFactory::instance();
    
    configManager.save();
    Log::v("main", "----- terminate medici process. -----");
    return 0;
}
