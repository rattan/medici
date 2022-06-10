#include "uuid.h"

std::string Uuid::genNil() {
    return UUID_NIL;
}
std::string Uuid::gen1() {
    return UUID_NIL;
}
std::string Uuid::gen2() {
    return UUID_NIL;
}
std::string Uuid::gen3() {
    return UUID_NIL;
}
std::string Uuid::gen4() {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_int_distribution<int> dist(0, 15);
    static std::uniform_int_distribution<int> dist2(8, 11);
    std::stringstream uuid4;
    uuid4<<std::hex;
    for(int i=0;i<8;++i) {
        uuid4<<dist(mt);
    }
    uuid4<<"-";
    for(int i=0;i<4;++i) {
        uuid4<<dist(mt);
    }
    uuid4<<"-4";
    for(int i=0;i<3;++i) {
        uuid4<<dist(mt);
    }
    uuid4<<"-"<<dist2(mt);
    for(int i=0;i<3;++i) {
        uuid4<<dist(mt);
    }
    uuid4<<"-";
    for(int i=0;i<12;++i) {
        uuid4<<dist(mt);
    }
    return uuid4.str();
}
std::string Uuid::gen5() {
    return UUID_NIL;
}

std::string Uuid::gen(version ver = version::FOUR) {
    switch(ver) {
        case version::NIL:
        case version::ONE:
        case version::TWO:
        case version::THREE:
        case version::FIVE:
        return genNil();
        case version::FOUR:
        return gen4();
    }
}