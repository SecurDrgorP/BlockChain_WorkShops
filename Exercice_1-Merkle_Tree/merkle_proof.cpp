#include "merkle_proof.h"

MerkleProof::MerkleProof(const std::string& hash, bool isLeft)
    : hash_(hash), isLeft_(isLeft) {}