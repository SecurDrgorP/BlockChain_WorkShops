#ifndef BLOCK_POS_H
#define BLOCK_POS_H

#include <string>
#include <vector>
#include <ctime>

class BlockPoS {
private:
    int index_;
    std::time_t timestamp_;
    std::vector<std::string> transactions_;
    std::string previousHash_;
    std::string hash_;
    std::string validator_;  // Validateur qui a créé ce bloc
    std::string signature_;  // Signature du validateur
    
    std::string calculateHash() const;

public:
    BlockPoS(int index,
             const std::vector<std::string>& transactions,
             const std::string& previousHash,
             const std::string& validator);
    
    void signBlock();
    bool isValid() const;
    
    int getIndex() const { return index_; }
    std::time_t getTimestamp() const { return timestamp_; }
    const std::vector<std::string>& getTransactions() const { return transactions_; }
    const std::string& getPreviousHash() const { return previousHash_; }
    const std::string& getHash() const { return hash_; }
    const std::string& getValidator() const { return validator_; }
    
    void print() const;
};

#endif
