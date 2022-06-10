#pragma once

#include <string>
#include <random>
#include <sstream>

#define UUID_RE R"([\da-f]{8}-([\da-f]{4}-){3}[\da-f]{12})"
#define UUID_NIL R"(00000000-0000-0000-0000-000000000000)"

class Uuid {
    private:
    static std::string genNil();
    static std::string gen1();
    static std::string gen2();
    static std::string gen3();
    static std::string gen4();
    static std::string gen5();
    public:
    enum class version {
        NIL, ONE, TWO, THREE, FOUR, FIVE
    };

    static std::string gen(version ver = version::FOUR);
};