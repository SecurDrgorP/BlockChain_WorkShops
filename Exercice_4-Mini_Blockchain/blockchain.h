#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "validator.h"
#include <vector>
#include <memory>
#include <map>
#include <random>

class Blockchain {
private:
    std::vector<std::shared_ptr<Block>> chain_;
    std::map<std::string, Validator> validators_;
    std::mt19937 rng_;
    
    std::shared_ptr<Block> createGenesisBlock();
    std::string selectValidator();
    double getTotalStake() const;

public:
    Blockchain();
    
    void addValidator(const std::string& address, double stake);
    void addBlockPoW(const std::vector<Transaction>& transactions, int difficulty);
    void addBlockPoS(const std::vector<Transaction>& transactions);
    
    bool isChainValid() const;
    void print() const;
    void printValidators() const;
    void printStatistics() const;
    void printComparison() const;
    
    int getChainLength() const { return chain_.size(); }
    const std::shared_ptr<Block>& getLatestBlock() const { return chain_.back(); }
    const std::map<std::string, Validator>& getValidators() const { return validators_; }
};

#endif