#include "blockchain_pos.h"
#include <iostream>
#include <algorithm>

BlockchainPoS::BlockchainPoS() : rng_(std::random_device{}()) {
    chain_.push_back(createGenesisBlock());
}

std::shared_ptr<BlockPoS> BlockchainPoS::createGenesisBlock() {
    std::vector<std::string> genesisTx;
    genesisTx.push_back("Genesis Block - PoS");
    auto genesis = std::make_shared<BlockPoS>(0, genesisTx, "0", "System");
    
    std::cout << "🌱 Creating Genesis Block (PoS)...\n";
    genesis->signBlock();
    
    return genesis;
}

void BlockchainPoS::addValidator(const std::string& address, double stake) {
    if(stake < 32.0) {
        std::cout << "❌ Minimum stake is 32 ETH!\n";
        return;
    }
    
    validators_[address] = Validator(address, stake);
    std::cout << "✅ Validator " << address << " added with " 
              << stake << " ETH stake\n";
}

double BlockchainPoS::getTotalStake() const {
    double total = 0;
    for(std::map<std::string, Validator>::const_iterator it = validators_.begin(); 
        it != validators_.end(); ++it) {
        total += it->second.getStake();
    }
    return total;
}

std::string BlockchainPoS::selectValidator() {
    if(validators_.empty()) {
        throw std::runtime_error("No validators available!");
    }
    
    double totalStake = getTotalStake();
    std::uniform_real_distribution<double> dist(0.0, totalStake);
    double random = dist(rng_);
    
    double cumulative = 0;
    for(std::map<std::string, Validator>::iterator it = validators_.begin(); 
        it != validators_.end(); ++it) {
        cumulative += it->second.getStake();
        if(random <= cumulative) {
            return it->first;
        }
    }
    
    return validators_.begin()->first;
}

void BlockchainPoS::addBlock(const std::vector<std::string>& transactions) {
    int index = chain_.size();
    std::string previousHash = getLatestBlock()->getHash();
    
    std::string validatorAddress = selectValidator();
    std::cout << "🎲 Selected validator: " << validatorAddress 
              << " (stake: " << validators_[validatorAddress].getStake() << " ETH)\n";
    
    auto newBlock = std::make_shared<BlockPoS>(index, transactions, previousHash, validatorAddress);
    newBlock->signBlock();
    
    validators_[validatorAddress].incrementBlocksValidated();
    chain_.push_back(newBlock);
}

bool BlockchainPoS::isValid() const {
    for(size_t i = 1; i < chain_.size(); i++) {
        const auto& currentBlock = chain_[i];
        const auto& previousBlock = chain_[i - 1];
        
        if(!currentBlock->isValid()) {
            std::cout << "❌ Block " << i << " has invalid signature!\n";
            return false;
        }
        
        if(currentBlock->getPreviousHash() != previousBlock->getHash()) {
            std::cout << "❌ Block " << i << " has invalid previous hash!\n";
            return false;
        }
    }
    
    return true;
}

void BlockchainPoS::print() const {
    std::cout << "\n╔════════════════════════════════════════════╗\n";
    std::cout << "║        BLOCKCHAIN (Proof of Stake)        ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n\n";
    
    for(const auto& block : chain_) {
        block->print();
        std::cout << "\n";
    }
    
    std::cout << "Chain Length: " << chain_.size() << " blocks\n";
    std::cout << "Total Validators: " << validators_.size() << "\n";
    std::cout << "Total Stake: " << getTotalStake() << " ETH\n";
    std::cout << "Valid: " << (isValid() ? "✅ Yes" : "❌ No") << "\n";
}

void BlockchainPoS::printValidators() const {
    std::cout << "\n╔════════════════════════════════════════════╗\n";
    std::cout << "║            VALIDATORS                      ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n\n";
    
    for(std::map<std::string, Validator>::const_iterator it = validators_.begin(); 
        it != validators_.end(); ++it) {
        it->second.print();
        std::cout << "\n";
    }
}