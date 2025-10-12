#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block_pow.h"
#include <vector>
#include <memory>

class Blockchain {
private:
    std::vector<std::shared_ptr<Block>> chain_;
    int difficulty_;
    
    std::shared_ptr<Block> createGenesisBlock();

public:
    explicit Blockchain(int difficulty = 4);
    
    void addBlock(const std::vector<std::string>& transactions);
    bool isValid() const;
    void print() const;
    
    int getChainLength() const { return chain_.size(); }
    const std::shared_ptr<Block>& getLatestBlock() const { return chain_.back(); }
    int getDifficulty() const { return difficulty_; }
    void setDifficulty(int difficulty) { difficulty_ = difficulty; }
};

#endif
