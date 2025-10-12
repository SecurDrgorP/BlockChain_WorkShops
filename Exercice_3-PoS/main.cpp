#include "blockchain_pos.h"
#include "../Exercice_2-PoW/blockchain_pow.h"
#include <iostream>
#include <chrono>
#include <iomanip>

void testPoS() {
    std::cout << "╔════════════════════════════════════════════════════╗\n";
    std::cout << "║         PROOF OF STAKE - DEMONSTRATION             ║\n";
    std::cout << "╚════════════════════════════════════════════════════╝\n\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    BlockchainPoS blockchain;
    
    blockchain.addValidator("Alice", 100.0);
    blockchain.addValidator("Bob", 50.0);
    blockchain.addValidator("Charlie", 150.0);
    blockchain.addValidator("David", 75.0);
    
    std::cout << "\n";
    
    std::vector<std::string> tx1;
    tx1.push_back("TX1: Alice -> Bob: 10 ETH");
    tx1.push_back("TX2: Charlie -> David: 5 ETH");
    blockchain.addBlock(tx1);
    
    std::vector<std::string> tx2;
    tx2.push_back("TX3: Eve -> Frank: 3 ETH");
    blockchain.addBlock(tx2);
    
    std::vector<std::string> tx3;
    tx3.push_back("TX4: Grace -> Henry: 7 ETH");
    tx3.push_back("TX5: Ian -> Jack: 2 ETH");
    blockchain.addBlock(tx3);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "⏱️  Total time: " << duration.count() << " ms\n";
    std::cout << "📊 Average time per block: " 
              << duration.count() / blockchain.getChainLength() << " ms\n";
    
    blockchain.print();
    blockchain.printValidators();
}

void comparePoWvsPoS() {
    std::cout << "\n╔════════════════════════════════════════════════════╗\n";
    std::cout << "║       COMPARISON: Proof of Work vs Proof of Stake ║\n";
    std::cout << "╚════════════════════════════════════════════════════╝\n\n";
    
    const int NUM_BLOCKS = 5;
    
    std::cout << "🔨 Testing Proof of Work...\n\n";
    
    auto startPoW = std::chrono::high_resolution_clock::now();
    
    Blockchain blockchainPoW(4);
    for(int i = 1; i < NUM_BLOCKS; i++) {
        std::vector<std::string> tx;
        tx.push_back("TX" + std::to_string(i));
        blockchainPoW.addBlock(tx);
    }
    
    auto endPoW = std::chrono::high_resolution_clock::now();
    auto durationPoW = std::chrono::duration_cast<std::chrono::milliseconds>(endPoW - startPoW);
    
    std::cout << "\n💎 Testing Proof of Stake...\n\n";
    
    auto startPoS = std::chrono::high_resolution_clock::now();
    
    BlockchainPoS blockchainPoS;
    blockchainPoS.addValidator("Alice", 100.0);
    blockchainPoS.addValidator("Bob", 50.0);
    blockchainPoS.addValidator("Charlie", 150.0);
    
    for(int i = 1; i < NUM_BLOCKS; i++) {
        std::vector<std::string> tx;
        tx.push_back("TX" + std::to_string(i));
        blockchainPoS.addBlock(tx);
    }
    
    auto endPoS = std::chrono::high_resolution_clock::now();
    auto durationPoS = std::chrono::duration_cast<std::chrono::milliseconds>(endPoS - startPoS);
    
    std::cout << "\n";
    std::cout << "┌─────────────────────────────────────────────────────────────┐\n";
    std::cout << "│                    RESULTS                                  │\n";
    std::cout << "├─────────────────────────────────────────────────────────────┤\n";
    std::cout << "│                                                             │\n";
    
    std::cout << "│  Proof of Work (PoW):                                       │\n";
    std::cout << "│  ├─ Total Time: " << std::setw(6) << durationPoW.count() 
              << " ms                                      │\n";
    std::cout << "│  ├─ Avg/Block:  " << std::setw(6) << durationPoW.count() / NUM_BLOCKS 
              << " ms                                      │\n";
    std::cout << "│  └─ Difficulty: 4 (4 leading zeros)                        │\n";
    std::cout << "│                                                             │\n";
    
    std::cout << "│  Proof of Stake (PoS):                                      │\n";
    std::cout << "│  ├─ Total Time: " << std::setw(6) << durationPoS.count() 
              << " ms                                      │\n";
    std::cout << "│  ├─ Avg/Block:  " << std::setw(6) << durationPoS.count() / NUM_BLOCKS 
              << " ms                                      │\n";
    std::cout << "│  └─ Validators: 3 (Total stake: 300 ETH)                   │\n";
    std::cout << "│                                                             │\n";
    
    double speedup = (double)durationPoW.count() / (durationPoS.count() > 0 ? durationPoS.count() : 1);
    std::cout << "│  ⚡ PoS is " << std::fixed << std::setprecision(1) 
              << speedup << "x FASTER than PoW!                          │\n";
    std::cout << "│                                                             │\n";
    std::cout << "└─────────────────────────────────────────────────────────────┘\n";
    
    std::cout << "\n┌──────────────┬─────────────┬─────────────┬──────────────┐\n";
    std::cout << "│   Metric     │     PoW     │     PoS     │   Winner     │\n";
    std::cout << "├──────────────┼─────────────┼─────────────┼──────────────┤\n";
    std::cout << "│ Speed        │   " << std::setw(6) << durationPoW.count() / NUM_BLOCKS 
              << " ms │   " << std::setw(6) << durationPoS.count() / NUM_BLOCKS 
              << " ms │   PoS ✅     │\n";
    std::cout << "│ Energy       │    High ⚡⚡ │     Low 🌱  │   PoS ✅     │\n";
    std::cout << "│ Security     │    High 🛡️  │   Medium 🛡 │   PoW ✅     │\n";
    std::cout << "│ Decentralize │    High ⭐⭐ │   Medium ⭐  │   PoW ✅     │\n";
    std::cout << "└──────────────┴─────────────┴─────────────┴──────────────┘\n";
}

int main() {
    std::cout << "╔════════════════════════════════════════════════════╗\n";
    std::cout << "║   BLOCKCHAIN - PROOF OF STAKE IMPLEMENTATION       ║\n";
    std::cout << "║              Exercice 3                            ║\n";
    std::cout << "╚════════════════════════════════════════════════════╝\n\n";
    
    testPoS();
    comparePoWvsPoS();
    
    return 0;
}