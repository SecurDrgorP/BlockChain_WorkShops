#ifndef MERKLE_PROOF_H
#define MERKLE_PROOF_H

#include <string>

class MerkleProof {
private:
    std::string hash_;
    bool isLeft_;

public:
    MerkleProof(const std::string& hash, bool isLeft);
    
    const std::string& getHash() const { return hash_; }
    bool isLeft() const { return isLeft_; }
};

#endif