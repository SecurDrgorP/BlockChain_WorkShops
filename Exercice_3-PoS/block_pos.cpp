#include "block_pos.h"
#include "../Utils/hash_util.h"
#include <iostream>
#include <sstream>
#include <chrono>

BlockPoS::BlockPoS(int index,
                   const std::vector<std::string>& transactions,
                   const std::string& previousHash,
                   const std::string& validator)
    : index_(index),
      timestamp_(std::time(nullptr)),
      transactions_(transactions),
      previousHash_(previousHash),
      validator_(validator) {
    hash_ = calculateHash();
}

std::string BlockPoS::calculateHash() const {
    std::stringstream ss;
    ss << index_ << timestamp_ << previousHash_ << validator_;
    
    for(const auto& tx : transactions_) {
        ss << tx;
    }
    
    return HashUtil::sha256(ss.str());
}

void BlockPoS::signBlock() {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::cout << "🔏 Signing block " << index_ 
              << " by validator " << validator_ << "...\n";
    
    // Signature = hash(hash + validator)
    signature_ = HashUtil::sha256(hash_ + validator_);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "✅ Block signed!\n";
    std::cout << "   Validator: " << validator_ << "\n";
    std::cout << "   Hash: " << hash_.substr(0, 20) << "...\n";
    std::cout << "   Signature: " << signature_.substr(0, 20) << "...\n";
    std::cout << "   Time: " << duration.count() << " μs\n\n";
}

bool BlockPoS::isValid() const {
    if(hash_ != calculateHash()) {
        return false;
    }
    
    if(signature_.empty()) {
        return false;
    }
    
    return true;
}

void BlockPoS::print() const {
    std::cout << "┌─────────────────────────────────────────┐\n";
    std::cout << "│ Block #" << index_ << " (PoS)\n";
    std::cout << "├─────────────────────────────────────────┤\n";
    std::cout << "│ Timestamp: " << timestamp_ << "\n";
    std::cout << "│ Validator: " << validator_ << "\n";
    std::cout << "│ Previous Hash: " << previousHash_.substr(0, 16) << "...\n";
    std::cout << "│ Hash: " << hash_.substr(0, 16) << "...\n";
    std::cout << "│ Signature: " << signature_.substr(0, 16) << "...\n";
    std::cout << "│ Transactions:\n";
    for(size_t i = 0; i < transactions_.size(); i++) {
        std::cout << "│   " << (i + 1) << ". " << transactions_[i] << "\n";
    }
    std::cout << "└─────────────────────────────────────────┘\n";
}