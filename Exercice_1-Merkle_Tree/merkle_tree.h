#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include "merkle_node.h"
#include "merkle_proof.h"
#include <vector>
#include <string>
#include <memory>

class MerkleTree {
private:
    std::shared_ptr<MerkleNode> root_;
    std::vector<std::string> leafHashes_;
    std::vector<std::string> originalData_;
    
    std::vector<std::shared_ptr<MerkleNode>> createLeafNodes(const std::vector<std::string>& data);
    std::shared_ptr<MerkleNode> buildTreeRecursive(std::vector<std::shared_ptr<MerkleNode>>& nodes);
    int findLeafIndex(const std::string& targetHash) const;
    void printNode(const std::shared_ptr<MerkleNode>& node, int level, const std::string& prefix) const;

public:
    MerkleTree() = default;
    
    void build(const std::vector<std::string>& data);
    std::string getRoot() const;
    bool isEmpty() const { return root_ == nullptr; }
    
    std::vector<MerkleProof> generateProof(const std::string& data) const;
    static bool verifyProof(const std::string& data, 
                           const std::vector<MerkleProof>& proof, 
                           const std::string& expectedRoot);
    
    void print() const;
    void printLeaves() const;
    
    size_t getLeafCount() const { return leafHashes_.size(); }
    const std::vector<std::string>& getLeafHashes() const { return leafHashes_; }
};

#endif