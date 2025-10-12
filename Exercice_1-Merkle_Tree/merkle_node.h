#ifndef MERKLE_NODE_H
#define MERKLE_NODE_H

#include <string>
#include <memory>

class MerkleNode {
private:
    std::string hash_;
    std::shared_ptr<MerkleNode> left_;
    std::shared_ptr<MerkleNode> right_;

public:
    explicit MerkleNode(const std::string& hash);
    
    const std::string& getHash() const { return hash_; }
    std::shared_ptr<MerkleNode> getLeft() const { return left_; }
    std::shared_ptr<MerkleNode> getRight() const { return right_; }
    
    void setLeft(std::shared_ptr<MerkleNode> left) { left_ = left; }
    void setRight(std::shared_ptr<MerkleNode> right) { right_ = right; }
    
    bool isLeaf() const { return !left_ && !right_; }
};

#endif
