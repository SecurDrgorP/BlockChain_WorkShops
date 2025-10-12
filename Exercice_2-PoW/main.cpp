#include "blockchain_pow.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

void testDifficulty(int difficulty) {
    std::cout << "\n";
    std::cout << "════════════════════════════════════════════════════\n";
    std::cout << "  TEST: DIFFICULTY = " << difficulty << "\n";
    std::cout << "════════════════════════════════════════════════════\n\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    Blockchain blockchain(difficulty);
    
    // Ajouter quelques blocs
    blockchain.addBlock({"Alice -> Bob: 10 BTC", "Charlie -> David: 5 BTC"});
    blockchain.addBlock({"Eve -> Frank: 3 BTC"});
    blockchain.addBlock({"Grace -> Henry: 7 BTC", "Ian -> Jack: 2 BTC"});
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "⏱️  Total mining time: " << duration.count() << " ms\n";
    std::cout << "📊 Average time per block: " 
              << duration.count() / blockchain.getChainLength() << " ms\n";
    
    // Afficher la blockchain
    blockchain.print();
}

void demonstrateInvalidBlock() {
    std::cout << "\n";
    std::cout << "════════════════════════════════════════════════════\n";
    std::cout << "  DEMONSTRATION: TAMPERING DETECTION\n";
    std::cout << "════════════════════════════════════════════════════\n\n";
    
    Blockchain blockchain(3);
    
    blockchain.addBlock({"Alice -> Bob: 50 BTC"});
    blockchain.addBlock({"Charlie -> David: 30 BTC"});
    
    std::cout << "✅ Blockchain is valid: " << (blockchain.isValid() ? "Yes" : "No") << "\n\n";
    
    // Note: Dans une vraie implémentation, on modifierait le bloc ici
    // Mais notre structure utilise des pointeurs constants
    std::cout << "⚠️  If we were to tamper with a block, the blockchain would become invalid!\n";
    std::cout << "   The hash chain would break, making tampering detectable.\n";
}

void compareDifficulties() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════╗\n";
    std::cout << "║     PROOF OF WORK - DIFFICULTY COMPARISON          ║\n";
    std::cout << "╚════════════════════════════════════════════════════╝\n";
    
    std::vector<int> difficulties = {1, 2, 3, 4, 5};
    
    std::cout << "\n┌──────────────┬───────────────┬──────────────────┐\n";
    std::cout << "│ Difficulty   │ Total Time    │ Avg Time/Block   │\n";
    std::cout << "├──────────────┼───────────────┼──────────────────┤\n";
    
    for(int diff : difficulties) {
        auto start = std::chrono::high_resolution_clock::now();
        
        Blockchain blockchain(diff);
        blockchain.addBlock({"TX1"});
        blockchain.addBlock({"TX2"});
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        std::cout << "│      " << diff << "       │   " 
                  << std::setw(6) << duration.count() << " ms   │    "
                  << std::setw(6) << duration.count() / blockchain.getChainLength() 
                  << " ms      │\n";
    }
    
    std::cout << "└──────────────┴───────────────┴──────────────────┘\n";
}

int main() {
    std::cout << "╔════════════════════════════════════════════════════╗\n";
    std::cout << "║   BLOCKCHAIN - PROOF OF WORK IMPLEMENTATION        ║\n";
    std::cout << "║              Exercice 2                            ║\n";
    std::cout << "╚════════════════════════════════════════════════════╝\n";
    
    // Test 1: Difficulté faible
    testDifficulty(2);
    
    // Test 2: Difficulté moyenne
    testDifficulty(4);
    
    // Test 3: Comparaison des difficultés
    compareDifficulties();
    
    // Test 4: Démonstration de la détection de modification
    demonstrateInvalidBlock();
    
    return 0;
}