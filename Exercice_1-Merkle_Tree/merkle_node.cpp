#include "merkle_node.h"

MerkleNode::MerkleNode(const std::string& hash)
    : hash_(hash), left_(nullptr), right_(nullptr) {}