#include "blockchain_pow.h"
#include <iostream>

Blockchain::Blockchain(int difficulty) : difficulty_(difficulty) {
    chain_.push_back(createGenesisBlock());
}

std::shared_ptr<Block> Blockchain::createGenesisBlock() {
    std::vector<std::string> genesisTx = {"Genesis Block"};
    auto genesis = std::make_shared<Block>(0, genesisTx, "0", difficulty_);
    std::cout << "🌱 Creating Genesis Block...\n";
    genesis->mineBlock();
    return genesis;
}

void Blockchain::addBlock(const std::vector<std::string>& transactions) {
    int index = chain_.size();
    std::string previousHash = getLatestBlock()->getHash();
    
    auto newBlock = std::make_shared<Block>(index, transactions, previousHash, difficulty_);
    newBlock->mineBlock();
    chain_.push_back(newBlock);
}

bool Blockchain::isValid() const {
    for(size_t i = 1; i < chain_.size(); i++) {
        const auto& currentBlock = chain_[i];
        const auto& previousBlock = chain_[i - 1];
        
        if(!currentBlock->isValid()) {
            std::cout << "❌ Block " << i << " has invalid hash!\n";
            return false;
        }
        
        if(currentBlock->getPreviousHash() != previousBlock->getHash()) {
            std::cout << "❌ Block " << i << " has invalid previous hash!\n";
            return false;
        }
    }
    
    return true;
}

void Blockchain::print() const {
    std::cout << "\n╔════════════════════════════════════════════╗\n";
    std::cout << "║           BLOCKCHAIN                       ║\n";
    std::cout << "╚════════════════════════════════════════════╝\n\n";
    
    for(const auto& block : chain_) {
        block->print();
        std::cout << "\n";
    }
    
    std::cout << "Chain Length: " << chain_.size() << " blocks\n";
    std::cout << "Difficulty: " << difficulty_ << "\n";
    std::cout << "Valid: " << (isValid() ? "✅ Yes" : "❌ No") << "\n";
}