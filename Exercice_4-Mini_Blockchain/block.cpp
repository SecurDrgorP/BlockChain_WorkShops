#include "block.h"
#include "../Utils/hash_util.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

Block::Block(int index,
             const std::vector<Transaction>& transactions,
             const std::string& previousHash)
    : index_(index),
      timestamp_(std::time(nullptr)),
      transactions_(transactions),
      previousHash_(previousHash),
      nonce_(0),
      difficulty_(0),
      consensusType_(NONE),
      miningTime_(0) {
    calculateMerkleRoot();
    hash_ = calculateHash();
}

void Block::calculateMerkleRoot() {
    std::vector<std::string> txData;
    for(const auto& tx : transactions_) {
        txData.push_back(tx.toHash());
    }
    
    MerkleTree tree;
    tree.build(txData);
    merkleRoot_ = tree.getRoot();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index_ << timestamp_ << previousHash_ << merkleRoot_ 
       << nonce_ << validator_;
    return HashUtil::sha256(ss.str());
}

void Block::mineBlock(int difficulty) {
    difficulty_ = difficulty;
    consensusType_ = PROOF_OF_WORK;
    validator_ = "";
    
    std::string target(difficulty, '0');
    
    std::cout << "Mining block #" << index_ << " (difficulty: " << difficulty << ")..." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    while(hash_.substr(0, difficulty) != target) {
        nonce_++;
        hash_ = calculateHash();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    miningTime_ = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "Block #" << index_ << " mined successfully" << std::endl;
    std::cout << "   Nonce: " << nonce_ << std::endl;
    std::cout << "   Hash: " << hash_.substr(0, 20) << "..." << std::endl;
    std::cout << "   Time: " << miningTime_ << " ms" << std::endl << std::endl;
}

void Block::validateBlock(const std::string& validator) {
    validator_ = validator;
    consensusType_ = PROOF_OF_STAKE;
    difficulty_ = 0;
    nonce_ = 0;
    
    std::cout << "Validating block #" << index_ << " by " << validator << "..." << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    hash_ = calculateHash();
    
    auto end = std::chrono::high_resolution_clock::now();
    miningTime_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Block #" << index_ << " validated successfully" << std::endl;
    std::cout << "   Validator: " << validator << std::endl;
    std::cout << "   Hash: " << hash_.substr(0, 20) << "..." << std::endl;
    std::cout << "   Time: " << miningTime_ << " microseconds" << std::endl << std::endl;
}

bool Block::isValid() const {
    if(hash_ != calculateHash()) {
        return false;
    }
    
    if(consensusType_ == PROOF_OF_WORK && difficulty_ > 0) {
        std::string target(difficulty_, '0');
        return hash_.substr(0, difficulty_) == target;
    }
    
    return true;
}

void Block::print() const {
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "| Block #" << std::setw(3) << index_;
    
    if(consensusType_ == PROOF_OF_WORK) {
        std::cout << " [PoW - Difficulty: " << difficulty_ << "]";
    } else if(consensusType_ == PROOF_OF_STAKE) {
        std::cout << " [PoS - Validator: " << validator_ << "]";
    }
    std::cout << std::endl;
    
    std::cout << "+-----------------------------------------------------------+" << std::endl;
    std::cout << "| Timestamp:     " << timestamp_ << std::endl;
    std::cout << "| Previous Hash: " << previousHash_.substr(0, 16) << "..." << std::endl;
    std::cout << "| Merkle Root:   " << merkleRoot_.substr(0, 16) << "..." << std::endl;
    std::cout << "| Block Hash:    " << hash_.substr(0, 16) << "..." << std::endl;
    
    if(consensusType_ == PROOF_OF_WORK) {
        std::cout << "| Nonce:         " << nonce_ << std::endl;
        std::cout << "| Mining Time:   " << miningTime_ << " ms" << std::endl;
    } else if(consensusType_ == PROOF_OF_STAKE) {
        std::cout << "| Validation Time: " << miningTime_ << " microseconds" << std::endl;
    }
    
    std::cout << "|" << std::endl;
    std::cout << "| Transactions (" << transactions_.size() << "):" << std::endl;
    for(const auto& tx : transactions_) {
        std::cout << "|   " << tx.toString() << std::endl;
    }
    std::cout << "+-----------------------------------------------------------+" << std::endl;
}