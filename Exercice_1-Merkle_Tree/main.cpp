#include "merkle_tree.h"
#include <iostream>
#include <vector>

int main() {
    std::cout << "╔════════════════════════════════════════════════════╗\n";
    std::cout << "║   ARBRE DE MERKLE - VERSION REFACTORISÉE          ║\n";
    std::cout << "╚════════════════════════════════════════════════════╝\n\n";
    
    MerkleTree tree;
    
    // Exemple 1 : 4 transactions
    std::cout << "--- EXEMPLE 1 : 4 Transactions ---\n";
    std::vector<std::string> tx1;
    tx1.push_back("Alice envoie 10 BTC à Bob");
    tx1.push_back("Charlie envoie 5 BTC à David");
    tx1.push_back("Eve envoie 3 BTC à Frank");
    tx1.push_back("Grace envoie 7 BTC à Henry");
    
    tree.build(tx1);
    tree.print();
    tree.printLeaves();
    std::cout << "Racine: " << tree.getRoot() << "\n\n";
    
    // Exemple 2 : Preuve de Merkle
    std::cout << "--- EXEMPLE 2 : Preuve de Merkle ---\n";
    std::string dataToProve = "Charlie envoie 5 BTC à David";
    std::cout << "Génération de preuve pour: " << dataToProve << "\n";
    
    auto proof = tree.generateProof(dataToProve);
    std::cout << "\nPreuve (" << proof.size() << " étapes):\n";
    for(size_t i = 0; i < proof.size(); i++) {
        std::cout << "  " << (i + 1) << ". " 
                  << proof[i].getHash().substr(0, 16) << "... "
                  << (proof[i].isLeft() ? "(gauche)" : "(droite)") << "\n";
    }
    
    bool valid = MerkleTree::verifyProof(dataToProve, proof, tree.getRoot());
    std::cout << "\n✓ Vérification: " << (valid ? "VALIDE" : "INVALIDE") << "\n";
    
    bool invalid = MerkleTree::verifyProof("TX incorrecte", proof, tree.getRoot());
    std::cout << "✗ Donnée incorrecte: " << (invalid ? "VALIDE" : "INVALIDE") << "\n";
    
    return 0;
}