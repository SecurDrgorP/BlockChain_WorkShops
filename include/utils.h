#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Convertit une chaîne de caractères en un vecteur de bits
std::vector<int> string_to_bits(const std::string& input);

// Convertit un vecteur de bits en une chaîne hexadécimale
std::string bits_to_hex_string(const std::vector<int>& bits);

#endif // UTILS_H
