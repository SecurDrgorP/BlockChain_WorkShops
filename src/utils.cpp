#include "utils.h"
#include <sstream>
#include <iomanip>
#include <bitset>

// Chaque caractère est converti en 8 bits
std::vector<int> string_to_bits(const std::string& input) {
    std::vector<int> bits;
    bits.reserve(input.length() * 8);
    for (char c : input) {
        std::bitset<8> b(c);
        for (int i = 0; i < 8; ++i) {
            bits.push_back(b[i]);
        }
    }
    return bits;
}

// Convertit des groupes de 4 bits en un caractère hexadécimal
std::string bits_to_hex_string(const std::vector<int>& bits) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < bits.size(); i += 4) {
        int val = 0;
        for (size_t j = 0; j < 4 && (i + j) < bits.size(); ++j) {
            val |= (bits[i + j] << (3 - j));
        }
        ss << std::setw(1) << val;
    }
    
    return ss.str();
}
