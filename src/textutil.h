# pragma once

class TextUtil {
public:
    constexpr static unsigned long long hash(const char* key) {
        return key[0] ? static_cast<unsigned long long>(key[0]) + 0xEDB8832Full * TextUtil::hash(key + 1) : 8603;
    }
};
