#ifndef BLOCKCHAIN_POS_H
#define BLOCKCHAIN_POS_H

#include "block_pos.h"
#include "validator.h"
#include <vector>
#include <memory>
#include <map>
#include <random>

class BlockchainPoS {
private:
    std::vector<std::shared_ptr<BlockPoS>> chain_;
    std::map<std::string, Validator> validators_;
    std::mt19937 rng_;
    
    std::shared_ptr<BlockPoS> createGenesisBlock();
    std::string selectValidator();
    double getTotalStake() const;

public:
    BlockchainPoS();
    
    void addValidator(const std::string& address, double stake);
    void addBlock(const std::vector<std::string>& transactions);
    bool isValid() const;
    void print() const;
    void printValidators() const;
    
    int getChainLength() const { return chain_.size(); }
    const std::shared_ptr<BlockPoS>& getLatestBlock() const { return chain_.back(); }
    const std::map<std::string, Validator>& getValidators() const { return validators_; }
};

#endif
