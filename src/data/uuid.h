#pragma once

#include <string>
#include <random>
#include <sstream>
#include <regex>

#include "data.h"

#define UUID_RE R"uuid([\da-f]{8}-([\da-f]{4}-){3}[\da-f]{12})uuid"
#define UUID_NIL R"(00000000-0000-0000-0000-000000000000)"

namespace med {

class Uuid: public Data{
    private:
    static Uuid genNil();
    static Uuid gen1();
    static Uuid gen2();
    static Uuid gen3();
    static Uuid gen4();
    static Uuid gen5();

    unsigned long long _bitData[2]{0, 0};
    std::string _strData;

    public:
    enum class version {
        NIL, ONE, TWO, THREE, FOUR, FIVE
    };
    
    virtual const std::string toString() const;
    virtual const std::string tag() const;

    static Uuid nil();
    static Uuid gen(version ver = version::FOUR);
    Uuid(const std::string &uuid = "");
    bool operator==(const Uuid& other) const;
    bool operator!=(const Uuid& other) const;
    bool operator<(const Uuid& other) const;
    bool operator<=(const Uuid& other) const;
    bool operator>(const Uuid& other) const;
    bool operator>=(const Uuid& other) const;
};

}