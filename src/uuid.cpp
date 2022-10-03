#include "uuid.h"

const std::string Uuid::toString() const{
    return this->_strData;
}

const std::string Uuid::tag() const {
    return "UUID";
}

Uuid Uuid::genNil() {
    return Uuid(UUID_NIL);
}
Uuid Uuid::gen1() {
    return Uuid(UUID_NIL);
}
Uuid Uuid::gen2() {
    return Uuid(UUID_NIL);
}
Uuid Uuid::gen3() {
    return Uuid(UUID_NIL);
}
Uuid Uuid::gen4() {
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
    return Uuid(uuid4.str());
}
Uuid Uuid::gen5() {
    return Uuid(UUID_NIL);
}

Uuid Uuid::gen(version ver) {
    switch(ver) {
        case version::NIL:
        case version::ONE:
        case version::TWO:
        case version::THREE:
        case version::FIVE:
        return genNil();
        case version::FOUR:
        return gen4();
        default:
        return genNil();
    }
}

Uuid::Uuid(const std::string& uuid): _strData(uuid) {
    if(!std::regex_match(uuid, std::regex(UUID_RE))) {
        Uuid validUuid = Uuid::gen(version::FOUR);
        this->_strData = validUuid._strData;
    }
    int shift = 0;
    auto ci = this->_strData.begin();
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 16; ++j) {
            if (*ci == '-') {
                ++ci;
            }
            this->_bitData[i] |= (unsigned long long)(*ci & 0xF) << (4 * j);
        }
    }
}
bool Uuid::operator==(const Uuid& other) const {
    return this->_bitData[0] == other._bitData[0] && this->_bitData[1] == other._bitData[1];
}
bool Uuid::operator!=(const Uuid& other) const {
    return !(*this == other);
}

bool Uuid::operator<(const Uuid& other) const {
    return this->_bitData[0] == other._bitData[0] ? this->_bitData[1] < other._bitData[1] : this->_bitData[0] < other._bitData[0];
}

bool Uuid::operator<=(const Uuid& other) const {
    return !(*this > other);
}

bool Uuid::operator>(const Uuid& other) const {
    return this->_bitData[0] == other._bitData[0] ? this->_bitData[1] > other._bitData[1] : this->_bitData[0] > other._bitData[0];
}

bool Uuid::operator>=(const Uuid& other) const {
    return !(*this < other);
}
