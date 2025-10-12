#ifndef HASH_UTIL_H
#define HASH_UTIL_H

#include <string>

class HashUtil {
public:
    static std::string sha256(const std::string& data);
};

#endif
