#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <ctime>

class Block {
private:
    int index_;
    std::time_t timestamp_;
    std::vector<std::string> transactions_;
    std::string previousHash_;
    std::string hash_;
    int nonce_;
    int difficulty_;
    
    std::string calculateHash() const;

public:
    Block(int index, 
          const std::vector<std::string>& transactions,
          const std::string& previousHash,
          int difficulty = 4);
    
    void mineBlock();
    bool isValid() const;
    
    // Getters
    int getIndex() const { return index_; }
    std::time_t getTimestamp() const { return timestamp_; }
    const std::vector<std::string>& getTransactions() const { return transactions_; }
    const std::string& getPreviousHash() const { return previousHash_; }
    const std::string& getHash() const { return hash_; }
    int getNonce() const { return nonce_; }
    int getDifficulty() const { return difficulty_; }
    
    void print() const;
};

#endif