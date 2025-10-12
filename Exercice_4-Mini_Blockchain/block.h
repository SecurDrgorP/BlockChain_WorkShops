#ifndef BLOCK_H
#define BLOCK_H

#include "transaction.h"
#include "../Exercice_1-Merkle_Tree/merkle_tree.h"
#include <vector>
#include <string>
#include <ctime>

enum ConsensusType {
    PROOF_OF_WORK,
    PROOF_OF_STAKE,
    NONE
};

class Block {
private:
    int index_;
    std::time_t timestamp_;
    std::vector<Transaction> transactions_;
    std::string previousHash_;
    std::string merkleRoot_;
    std::string hash_;
    int nonce_;
    int difficulty_;
    std::string validator_;
    ConsensusType consensusType_;
    long miningTime_;
    
    std::string calculateHash() const;
    void calculateMerkleRoot();

public:
    Block(int index,
          const std::vector<Transaction>& transactions,
          const std::string& previousHash);
    
    void mineBlock(int difficulty);
    void validateBlock(const std::string& validator);
    bool isValid() const;
    
    int getIndex() const { return index_; }
    std::time_t getTimestamp() const { return timestamp_; }
    const std::vector<Transaction>& getTransactions() const { return transactions_; }
    const std::string& getPreviousHash() const { return previousHash_; }
    const std::string& getHash() const { return hash_; }
    const std::string& getMerkleRoot() const { return merkleRoot_; }
    int getNonce() const { return nonce_; }
    int getDifficulty() const { return difficulty_; }
    const std::string& getValidator() const { return validator_; }
    ConsensusType getConsensusType() const { return consensusType_; }
    long getMiningTime() const { return miningTime_; }
    
    void print() const;
};

#endif
