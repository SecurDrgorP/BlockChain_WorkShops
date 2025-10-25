#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <cstdint>
#include <vector>
#include <string>

enum HashType {
    AC_HASH,
    SHA256
};

struct Block {
    int index;
    std::string data;
    std::string prev_hash;
    time_t timestamp;
    long long nonce;
    std::string hash;

    Block(int idx, std::string d, std::string p_hash);
    std::string calculateHash(HashType type, uint8_t rule, size_t steps);
};

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty_sha256;
    // Add a separate, lower difficulty for our custom hash
    int difficulty_ac; 

public:
    Blockchain();
    long long addBlock(std::string data, HashType type, uint8_t rule = 30, size_t steps = 128);
    bool isChainValid();
    void printChain();
    Block getLastBlock() const;
};

#endif // BLOCKCHAIN_H
