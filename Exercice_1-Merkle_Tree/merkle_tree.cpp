#include "merkle_tree.h"
#include "../Utils/hash_util.h"
#include <iostream>
#include <algorithm>

std::vector<std::shared_ptr<MerkleNode>> 
MerkleTree::createLeafNodes(const std::vector<std::string>& data) {
    std::vector<std::shared_ptr<MerkleNode>> leaves;
    leafHashes_.clear();
    originalData_ = data;
    
    for(const auto& item : data) {
        std::string hash = HashUtil::sha256(item);
        leafHashes_.push_back(hash);
        leaves.push_back(std::make_shared<MerkleNode>(hash));
    }
    
    return leaves;
}

std::shared_ptr<MerkleNode> 
MerkleTree::buildTreeRecursive(std::vector<std::shared_ptr<MerkleNode>>& nodes) {
    if(nodes.empty()) return nullptr;
    if(nodes.size() == 1) return nodes[0];
    
    std::vector<std::shared_ptr<MerkleNode>> parentLevel;
    
    for(size_t i = 0; i < nodes.size(); i += 2) {
        auto left = nodes[i];
        auto right = (i + 1 < nodes.size()) ? nodes[i + 1] : nodes[i];
        
        std::string parentHash = HashUtil::sha256(left->getHash() + right->getHash());
        auto parent = std::make_shared<MerkleNode>(parentHash);
        parent->setLeft(left);
        parent->setRight(right);
        
        parentLevel.push_back(parent);
    }
    
    return buildTreeRecursive(parentLevel);
}

void MerkleTree::build(const std::vector<std::string>& data) {
    if(data.empty()) {
        root_ = nullptr;
        leafHashes_.clear();
        originalData_.clear();
        return;
    }
    
    auto leaves = createLeafNodes(data);
    root_ = buildTreeRecursive(leaves);
}

std::string MerkleTree::getRoot() const {
    return root_ ? root_->getHash() : "";
}

int MerkleTree::findLeafIndex(const std::string& targetHash) const {
    for(size_t i = 0; i < leafHashes_.size(); i++) {
        if(leafHashes_[i] == targetHash) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

std::vector<MerkleProof> 
MerkleTree::generateProof(const std::string& data) const {
    std::vector<MerkleProof> proof;
    std::string targetHash = HashUtil::sha256(data);
    
    int index = findLeafIndex(targetHash);
    if(index == -1) return proof;
    
    std::vector<std::string> currentLevel = leafHashes_;
    int currentIndex = index;
    
    while(currentLevel.size() > 1) {
        std::vector<std::string> nextLevel;
        
        for(size_t i = 0; i < currentLevel.size(); i += 2) {
            const std::string& left = currentLevel[i];
            const std::string& right = (i + 1 < currentLevel.size()) 
                ? currentLevel[i + 1] : currentLevel[i];
            
            if(i == static_cast<size_t>(currentIndex)) {
                if(i + 1 < currentLevel.size() && right != left) {
                    proof.push_back(MerkleProof(right, false));
                }
            } else if(i + 1 == static_cast<size_t>(currentIndex)) {
                proof.push_back(MerkleProof(left, true));
            }
            
            nextLevel.push_back(HashUtil::sha256(left + right));
        }
        
        currentIndex /= 2;
        currentLevel = nextLevel;
    }
    
    return proof;
}

bool MerkleTree::verifyProof(const std::string& data, 
                             const std::vector<MerkleProof>& proof, 
                             const std::string& expectedRoot) {
    std::string hash = HashUtil::sha256(data);
    
    for(const auto& step : proof) {
        hash = step.isLeft() 
            ? HashUtil::sha256(step.getHash() + hash)
            : HashUtil::sha256(hash + step.getHash());
    }
    
    return hash == expectedRoot;
}

void MerkleTree::printNode(const std::shared_ptr<MerkleNode>& node, 
                           int level, 
                           const std::string& prefix) const {
    if(!node) return;
    
    std::string indent(level * 4, ' ');
    std::string shortHash = node->getHash().substr(0, 16) + "...";
    std::cout << indent << prefix << shortHash << std::endl;
    
    if(!node->isLeaf()) {
        if(node->getLeft()) {
            printNode(node->getLeft(), level + 1, "L--- ");
        }
        if(node->getRight() && node->getRight() != node->getLeft()) {
            printNode(node->getRight(), level + 1, "R--- ");
        }
    }
}

void MerkleTree::print() const {
    if(isEmpty()) {
        std::cout << "L'arbre est vide." << std::endl;
        return;
    }
    
    std::cout << "\n=== Structure de l'Arbre de Merkle ===" << std::endl;
    printNode(root_, 0, "Root: ");
    std::cout << std::endl;
}

void MerkleTree::printLeaves() const {
    std::cout << "\n=== Feuilles de l'arbre ===" << std::endl;
    for(size_t i = 0; i < leafHashes_.size(); i++) {
        std::cout << "Feuille " << i << ": " 
                  << leafHashes_[i].substr(0, 16) << "..." << std::endl;
    }
    std::cout << std::endl;
}