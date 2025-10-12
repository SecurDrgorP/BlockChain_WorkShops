#include "blockchain.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Blockchain::Blockchain() : rng_(std::random_device{}()) {
    chain_.push_back(createGenesisBlock());
}

std::shared_ptr<Block> Blockchain::createGenesisBlock() {
    std::vector<Transaction> genesisTx;
    genesisTx.push_back(Transaction("0", "System", "Genesis", 0.0));
    
    auto genesis = std::make_shared<Block>(0, genesisTx, "0");
    
    std::cout << "Creating Genesis Block..." << std::endl;
    genesis->mineBlock(2);
    
    return genesis;
}

void Blockchain::addValidator(const std::string& address, double stake) {
    if(stake < 32.0) {
        std::cout << "ERROR: Minimum stake is 32 ETH. Validator " << address << " rejected." << std::endl;
        return;
    }
    
    validators_[address] = Validator(address, stake);
    std::cout << "Validator " << address << " added with " 
              << std::fixed << std::setprecision(2) << stake << " ETH" << std::endl;
}

double Blockchain::getTotalStake() const {
    double total = 0;
    for(std::map<std::string, Validator>::const_iterator it = validators_.begin();
        it != validators_.end(); ++it) {
        total += it->second.getStake();
    }
    return total;
}

std::string Blockchain::selectValidator() {
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

void Blockchain::addBlockPoW(const std::vector<Transaction>& transactions, int difficulty) {
    int index = chain_.size();
    std::string previousHash = getLatestBlock()->getHash();
    
    auto newBlock = std::make_shared<Block>(index, transactions, previousHash);
    newBlock->mineBlock(difficulty);
    
    chain_.push_back(newBlock);
}

void Blockchain::addBlockPoS(const std::vector<Transaction>& transactions) {
    int index = chain_.size();
    std::string previousHash = getLatestBlock()->getHash();
    
    std::string validatorAddress = selectValidator();
    std::cout << "Selected validator: " << validatorAddress 
              << " (stake: " << std::fixed << std::setprecision(2) 
              << validators_[validatorAddress].getStake() << " ETH)" << std::endl;
    
    auto newBlock = std::make_shared<Block>(index, transactions, previousHash);
    newBlock->validateBlock(validatorAddress);
    
    validators_[validatorAddress].incrementBlocksValidated();
    validators_[validatorAddress].addReward(0.1);
    
    chain_.push_back(newBlock);
}

bool Blockchain::isChainValid() const {
    for(size_t i = 1; i < chain_.size(); i++) {
        const auto& currentBlock = chain_[i];
        const auto& previousBlock = chain_[i - 1];
        
        if(!currentBlock->isValid()) {
            std::cout << "ERROR: Block " << i << " is invalid!" << std::endl;
            return false;
        }
        
        if(currentBlock->getPreviousHash() != previousBlock->getHash()) {
            std::cout << "ERROR: Block " << i << " has invalid previous hash!" << std::endl;
            return false;
        }
    }
    
    return true;
}

void Blockchain::print() const {
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "                  MINI BLOCKCHAIN                           " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    for(const auto& block : chain_) {
        block->print();
        std::cout << std::endl;
    }
    
    std::cout << "Chain Status:" << std::endl;
    std::cout << "  Total Blocks: " << chain_.size() << std::endl;
    std::cout << "  Chain Valid: " << (isChainValid() ? "Yes" : "No") << std::endl;
}

void Blockchain::printValidators() const {
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "                    VALIDATORS                              " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    if(validators_.empty()) {
        std::cout << "  No validators registered." << std::endl;
        return;
    }
    
    for(std::map<std::string, Validator>::const_iterator it = validators_.begin();
        it != validators_.end(); ++it) {
        it->second.print();
    }
    
    std::cout << std::endl;
    std::cout << "  Total Stake: " << std::fixed << std::setprecision(2) 
              << getTotalStake() << " ETH" << std::endl;
}

void Blockchain::printStatistics() const {
    int powBlocks = 0;
    int posBlocks = 0;
    long totalPoWTime = 0;
    long totalPoSTime = 0;
    int totalTransactions = 0;
    
    for(const auto& block : chain_) {
        totalTransactions += block->getTransactions().size();
        
        if(block->getConsensusType() == PROOF_OF_WORK) {
            powBlocks++;
            totalPoWTime += block->getMiningTime();
        } else if(block->getConsensusType() == PROOF_OF_STAKE) {
            posBlocks++;
            totalPoSTime += block->getMiningTime();
        }
    }
    
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "                    STATISTICS                              " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Blocks:" << std::endl;
    std::cout << "  Total Blocks:       " << chain_.size() << std::endl;
    std::cout << "  PoW Blocks:         " << powBlocks << std::endl;
    std::cout << "  PoS Blocks:         " << posBlocks << std::endl;
    std::cout << "  Total Transactions: " << totalTransactions << std::endl;
    std::cout << std::endl;
    
    std::cout << "Performance:" << std::endl;
    if(powBlocks > 0) {
        std::cout << "  PoW Total Time:     " << totalPoWTime << " ms" << std::endl;
        std::cout << "  PoW Avg Time:       " << totalPoWTime / powBlocks << " ms/block" << std::endl;
    }
    if(posBlocks > 0) {
        std::cout << "  PoS Total Time:     " << totalPoSTime << " microseconds" << std::endl;
        std::cout << "  PoS Avg Time:       " << totalPoSTime / posBlocks << " microseconds/block" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Validators:" << std::endl;
    std::cout << "  Total Validators:   " << validators_.size() << std::endl;
    std::cout << "  Total Stake:        " << std::fixed << std::setprecision(2) 
              << getTotalStake() << " ETH" << std::endl;
}

void Blockchain::printComparison() const {
    int powBlocks = 0;
    int posBlocks = 0;
    long totalPoWTime = 0;
    long totalPoSTime = 0;
    
    for(const auto& block : chain_) {
        if(block->getConsensusType() == PROOF_OF_WORK) {
            powBlocks++;
            totalPoWTime += block->getMiningTime();
        } else if(block->getConsensusType() == PROOF_OF_STAKE) {
            posBlocks++;
            totalPoSTime += block->getMiningTime();
        }
    }
    
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "            PROOF OF WORK vs PROOF OF STAKE                 " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    std::cout << "+-------------------+-----------------+-----------------+" << std::endl;
    std::cout << "| Metric            |   Proof of Work |  Proof of Stake |" << std::endl;
    std::cout << "+-------------------+-----------------+-----------------+" << std::endl;
    
    std::cout << "| Blocks            |" << std::setw(16) << powBlocks 
              << " |" << std::setw(16) << posBlocks << " |" << std::endl;
    
    if(powBlocks > 0) {
        std::cout << "| Total Time        |" << std::setw(12) << totalPoWTime << " ms |";
    } else {
        std::cout << "| Total Time        |" << std::setw(16) << "N/A |";
    }
    
    if(posBlocks > 0) {
        std::cout << std::setw(9) << totalPoSTime << " us |" << std::endl;
    } else {
        std::cout << std::setw(16) << "N/A |" << std::endl;
    }
    
    if(powBlocks > 0) {
        std::cout << "| Avg Time/Block    |" << std::setw(12) << totalPoWTime / powBlocks << " ms |";
    } else {
        std::cout << "| Avg Time/Block    |" << std::setw(16) << "N/A |";
    }
    
    if(posBlocks > 0) {
        std::cout << std::setw(9) << totalPoSTime / posBlocks << " us |" << std::endl;
    } else {
        std::cout << std::setw(16) << "N/A |" << std::endl;
    }
    
    std::cout << "| Energy            |            High |             Low |" << std::endl;
    std::cout << "| Speed             |            Slow |            Fast |" << std::endl;
    std::cout << "| Decentralization  |            High |          Medium |" << std::endl;
    std::cout << "| Security          |            High |          Medium |" << std::endl;
    std::cout << "+-------------------+-----------------+-----------------+" << std::endl;
    
    if(powBlocks > 0 && posBlocks > 0) {
        double speedup = (double)(totalPoWTime * 1000) / totalPoSTime;
        std::cout << std::endl;
        std::cout << "PoS is approximately " << std::fixed << std::setprecision(0) 
                  << speedup << "x FASTER than PoW" << std::endl;
    }
}