#include "application.h"

// medici process start position.
// program will run in Application class.

int main(int argc, char* argv[]) {
    med::Application app(argc, argv);
    return app.exec();
}
