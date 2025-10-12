#include "block_pow.h"
#include "../Utils/hash_util.h"
#include <iostream>
#include <sstream>
#include <chrono>

Block::Block(int index, 
             const std::vector<std::string>& transactions,
             const std::string& previousHash,
             int difficulty)
    : index_(index),
      timestamp_(std::time(nullptr)),
      transactions_(transactions),
      previousHash_(previousHash),
      nonce_(0),
      difficulty_(difficulty) {
    hash_ = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index_ << timestamp_ << previousHash_ << nonce_;
    
    for(const auto& tx : transactions_) {
        ss << tx;
    }
    
    return HashUtil::sha256(ss.str());
}

void Block::mineBlock() {
    std::string target(difficulty_, '0');
    
    std::cout << "⛏️  Mining block " << index_ << " (difficulty: " 
              << difficulty_ << ")...\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    while(hash_.substr(0, difficulty_) != target) {
        nonce_++;
        hash_ = calculateHash();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "✅ Block mined!\n";
    std::cout << "   Nonce: " << nonce_ << "\n";
    std::cout << "   Hash: " << hash_.substr(0, 20) << "...\n";
    std::cout << "   Time: " << duration.count() << " ms\n\n";
}

bool Block::isValid() const {
    if(hash_ != calculateHash()) {
        return false;
    }
    
    std::string target(difficulty_, '0');
    return hash_.substr(0, difficulty_) == target;
}

void Block::print() const {
    std::cout << "┌─────────────────────────────────────────┐\n";
    std::cout << "│ Block #" << index_ << "\n";
    std::cout << "├─────────────────────────────────────────┤\n";
    std::cout << "│ Timestamp: " << timestamp_ << "\n";
    std::cout << "│ Previous Hash: " << previousHash_.substr(0, 16) << "...\n";
    std::cout << "│ Hash: " << hash_.substr(0, 16) << "...\n";
    std::cout << "│ Nonce: " << nonce_ << "\n";
    std::cout << "│ Difficulty: " << difficulty_ << "\n";
    std::cout << "│ Transactions:\n";
    for(size_t i = 0; i < transactions_.size(); i++) {
        std::cout << "│   " << (i + 1) << ". " << transactions_[i] << "\n";
    }
    std::cout << "└─────────────────────────────────────────┘\n";
}
