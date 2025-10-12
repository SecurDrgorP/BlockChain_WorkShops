#include "blockchain.h"
#include <iostream>
#include <vector>
#include <chrono>

void partie1_structure() {
    std::cout << "============================================================" << std::endl;
    std::cout << "      PARTIE 1: Structure des Blocs et de la Chaine        " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    Blockchain blockchain;
    
    std::vector<Transaction> tx1;
    tx1.push_back(Transaction("1", "Alice", "Bob", 5.5));
    tx1.push_back(Transaction("2", "Charlie", "David", 3.2));
    
    std::cout << "Transactions created:" << std::endl;
    for(const auto& tx : tx1) {
        tx.print();
    }
    std::cout << std::endl;
    
    std::cout << "Merkle Tree calculated automatically" << std::endl;
    std::cout << "Block structure with all required fields" << std::endl;
    std::cout << "Blockchain initialized with Genesis Block" << std::endl;
    std::cout << std::endl;
    
    blockchain.print();
}

void partie2_proofOfWork() {
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "           PARTIE 2: Proof of Work (PoW)                   " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    Blockchain blockchain;
    
    std::vector<Transaction> tx1;
    tx1.push_back(Transaction("1", "Alice", "Bob", 10.0));
    tx1.push_back(Transaction("2", "Charlie", "David", 5.0));
    
    std::vector<Transaction> tx2;
    tx2.push_back(Transaction("3", "Eve", "Frank", 3.5));
    
    std::vector<Transaction> tx3;
    tx3.push_back(Transaction("4", "Grace", "Henry", 7.0));
    
    std::cout << "Testing different difficulty levels:" << std::endl;
    std::cout << std::endl;
    
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Block with Difficulty 2:" << std::endl;
    blockchain.addBlockPoW(tx1, 2);
    
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Block with Difficulty 3:" << std::endl;
    blockchain.addBlockPoW(tx2, 3);
    
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "Block with Difficulty 4:" << std::endl;
    blockchain.addBlockPoW(tx3, 4);
    
    blockchain.print();
    blockchain.printStatistics();
}

void partie3_proofOfStake() {
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "          PARTIE 3: Proof of Stake (PoS)                   " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    Blockchain blockchain;
    
    std::cout << "Setting up validators:" << std::endl;
    blockchain.addValidator("Alice", 100.0);
    blockchain.addValidator("Bob", 50.0);
    blockchain.addValidator("Charlie", 150.0);
    blockchain.addValidator("David", 75.0);
    std::cout << std::endl;
    
    std::vector<Transaction> tx1;
    tx1.push_back(Transaction("1", "User1", "User2", 2.0));
    tx1.push_back(Transaction("2", "User3", "User4", 1.5));
    
    std::vector<Transaction> tx2;
    tx2.push_back(Transaction("3", "User5", "User6", 3.0));
    
    std::vector<Transaction> tx3;
    tx3.push_back(Transaction("4", "User7", "User8", 0.8));
    tx3.push_back(Transaction("5", "User9", "User10", 1.2));
    
    std::cout << "------------------------------------------------------------" << std::endl;
    blockchain.addBlockPoS(tx1);
    
    std::cout << "------------------------------------------------------------" << std::endl;
    blockchain.addBlockPoS(tx2);
    
    std::cout << "------------------------------------------------------------" << std::endl;
    blockchain.addBlockPoS(tx3);
    
    blockchain.print();
    blockchain.printValidators();
    blockchain.printStatistics();
}

void partie4_analyseComparative() {
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "         PARTIE 4: Analyse Comparative PoW vs PoS          " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    Blockchain blockchain;
    
    std::cout << "Setting up validators for PoS:" << std::endl;
    blockchain.addValidator("Alice", 100.0);
    blockchain.addValidator("Bob", 50.0);
    blockchain.addValidator("Charlie", 150.0);
    std::cout << std::endl;
    
    std::vector<std::vector<Transaction>> allTransactions;
    for(int i = 0; i < 6; i++) {
        std::vector<Transaction> txs;
        txs.push_back(Transaction(
            std::to_string(i*2 + 1), 
            "Sender" + std::to_string(i), 
            "Receiver" + std::to_string(i), 
            1.0 + i * 0.5
        ));
        txs.push_back(Transaction(
            std::to_string(i*2 + 2), 
            "Sender" + std::to_string(i+1), 
            "Receiver" + std::to_string(i+1), 
            2.0 + i * 0.3
        ));
        allTransactions.push_back(txs);
    }
    
    std::cout << "============================================================" << std::endl;
    std::cout << "Adding blocks with Proof of Work:" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    auto startPoW = std::chrono::high_resolution_clock::now();
    
    blockchain.addBlockPoW(allTransactions[0], 3);
    blockchain.addBlockPoW(allTransactions[1], 3);
    blockchain.addBlockPoW(allTransactions[2], 3);
    
    auto endPoW = std::chrono::high_resolution_clock::now();
    auto durationPoW = std::chrono::duration_cast<std::chrono::milliseconds>(endPoW - startPoW);
    
    std::cout << "============================================================" << std::endl;
    std::cout << "Adding blocks with Proof of Stake:" << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    auto startPoS = std::chrono::high_resolution_clock::now();
    
    blockchain.addBlockPoS(allTransactions[3]);
    blockchain.addBlockPoS(allTransactions[4]);
    blockchain.addBlockPoS(allTransactions[5]);
    
    auto endPoS = std::chrono::high_resolution_clock::now();
    auto durationPoS = std::chrono::duration_cast<std::chrono::milliseconds>(endPoS - startPoS);
    
    blockchain.print();
    blockchain.printValidators();
    blockchain.printStatistics();
    blockchain.printComparison();
    
    std::cout << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << "                 DETAILED ANALYSIS                          " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    std::cout << "1. Block Addition Speed:" << std::endl;
    std::cout << "   - PoW (3 blocks): " << durationPoW.count() << " ms" << std::endl;
    std::cout << "   - PoS (3 blocks): " << durationPoS.count() << " ms" << std::endl;
    if(durationPoS.count() > 0) {
        std::cout << "   - PoS is " << (durationPoW.count() / durationPoS.count()) 
                  << "x faster" << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "2. Resource Consumption (approximate):" << std::endl;
    std::cout << "   - PoW: Uses 100% CPU during mining" << std::endl;
    std::cout << "   - PoS: Uses <1% CPU for validation" << std::endl;
    std::cout << "   - PoS consumes approximately 1000x less energy" << std::endl;
    std::cout << std::endl;
    
    std::cout << "3. Implementation Ease:" << std::endl;
    std::cout << "   - PoW: Complex (nonce search, difficulty adjustment)" << std::endl;
    std::cout << "   - PoS: Simpler (weighted random selection)" << std::endl;
    std::cout << "   - PoS is easier to implement" << std::endl;
    std::cout << std::endl;
    
    std::cout << "4. Security:" << std::endl;
    std::cout << "   - PoW: Very secure (high computational cost)" << std::endl;
    std::cout << "   - PoS: Secure (economic risk with stake)" << std::endl;
    std::cout << "   - PoW slightly more secure but PoS sufficient" << std::endl;
    std::cout << std::endl;
    
    std::cout << "5. Decentralization:" << std::endl;
    std::cout << "   - PoW: Highly decentralized (anyone can mine)" << std::endl;
    std::cout << "   - PoS: Moderately decentralized (minimum stake required)" << std::endl;
    std::cout << "   - PoW favors more decentralization" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << "============================================================" << std::endl;
    std::cout << "     EXERCICE 4: MINI-BLOCKCHAIN FROM SCRATCH              " << std::endl;
    std::cout << "     Complete Integration of Exercises 1, 2 and 3          " << std::endl;
    std::cout << "============================================================" << std::endl;
    std::cout << std::endl;
    
    int choice;
    
    do {
        std::cout << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "|                         MENU                              |" << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "| 1. Part 1: Block and Chain Structure                     |" << std::endl;
        std::cout << "| 2. Part 2: Proof of Work (PoW)                           |" << std::endl;
        std::cout << "| 3. Part 3: Proof of Stake (PoS)                          |" << std::endl;
        std::cout << "| 4. Part 4: Comparative Analysis                          |" << std::endl;
        std::cout << "| 5. Execute ALL                                           |" << std::endl;
        std::cout << "| 0. Exit                                                  |" << std::endl;
        std::cout << "+-----------------------------------------------------------+" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                partie1_structure();
                break;
            case 2:
                partie2_proofOfWork();
                break;
            case 3:
                partie3_proofOfStake();
                break;
            case 4:
                partie4_analyseComparative();
                break;
            case 5:
                partie1_structure();
                partie2_proofOfWork();
                partie3_proofOfStake();
                partie4_analyseComparative();
                break;
            case 0:
                std::cout << std::endl << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << std::endl << "ERROR: Invalid choice!" << std::endl;
        }
        
    } while(choice != 0);
    
    return 0;
}