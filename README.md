# Mini Blockchain - Implementation from Scratch in C++

A complete blockchain implementation in C++ featuring Merkle Trees, Proof of Work (PoW), and Proof of Stake (PoS) consensus mechanisms.

## Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Exercises](#exercises)
  - [Exercise 1: Merkle Tree](#exercise-1-merkle-tree)
  - [Exercise 2: Proof of Work](#exercise-2-proof-of-work)
  - [Exercise 3: Proof of Stake](#exercise-3-proof-of-stake)
  - [Exercise 4: Complete Mini-Blockchain](#exercise-4-complete-mini-blockchain)
- [Compilation](#compilation)
- [Usage](#usage)
- [Features](#features)
- [Performance Comparison](#performance-comparison)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project implements a functional blockchain from scratch in C++, demonstrating core blockchain concepts including:

- **Merkle Trees** for transaction verification
- **Proof of Work (PoW)** consensus mechanism with adjustable difficulty
- **Proof of Stake (PoS)** consensus mechanism with validator selection
- **Block structure** with transactions, hashing, and chain validation
- **Performance analysis** comparing PoW and PoS

## Project Structure

```
Mini-Blockchain/
│
├── Utils/
│   ├── hash_util.h
│   └── hash_util.cpp
│
├── Exercice_1-Merkle_Tree/
│   ├── merkle_node.h
│   ├── merkle_node.cpp
│   ├── merkle_proof.h
│   ├── merkle_proof.cpp
│   ├── merkle_tree.h
│   ├── merkle_tree.cpp
│   └── main.cpp
│
├── Exercice_2-PoW/
│   ├── block.h
│   ├── block.cpp
│   ├── blockchain.h
│   ├── blockchain.cpp
│   └── main.cpp
│
├── Exercice_3-PoS/
│   ├── validator.h
│   ├── validator.cpp
│   ├── block_pos.h
│   ├── block_pos.cpp
│   ├── blockchain_pos.h
│   ├── blockchain_pos.cpp
│   └── main.cpp
│
├── Exercice_4-Mini_Blockchain/
│   ├── transaction.h
│   ├── transaction.cpp
│   ├── validator.h
│   ├── validator.cpp
│   ├── block.h
│   ├── block.cpp
│   ├── blockchain.h
│   ├── blockchain.cpp
│   └── main.cpp
│
└── README.md
```

## Prerequisites

### Required

- **C++ Compiler**: g++ with C++14 support or higher
- **OpenSSL**: For SHA-256 hashing

### Installation on Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install g++ libssl-dev
```

### Installation on macOS

```bash
brew install openssl
```

### Installation on Windows

Use MinGW or WSL with the Ubuntu instructions above.

## Installation

1. Clone the repository:
```bash
git clone <repository-url>
cd Mini-Blockchain
```

2. Create the Utils directory and add hash utilities:
```bash
mkdir -p Utils
```

## Exercises

### Exercise 1: Merkle Tree

Implementation of a Merkle Tree data structure for efficient transaction verification.

**Features:**
- Build Merkle Tree from transaction data
- Calculate Merkle Root
- Generate Merkle Proofs
- Verify transaction inclusion

**Compilation:**
```bash
cd Exercice_1-Merkle_Tree
g++ -std=c++14 -o merkle \
    ../Utils/hash_util.cpp \
    merkle_node.cpp \
    merkle_proof.cpp \
    merkle_tree.cpp \
    main.cpp \
    -I../Utils \
    -lssl -lcrypto
```

**Execution:**
```bash
./merkle
```

**Example Output:**
```
=== Structure de l'Arbre de Merkle ===
Root: 3a4b5c6d7e8f9a0b...
    L--- 8e7f9a2b3c4d5e6f...
        L--- a591a6d40bf420...
        R--- 7c7d8c5a8f9e3b...
    R--- 4d5e6f7a8b9c0d1e...
        L--- 9f2c3d4e5a6b7c...
        R--- 1a2b3c4d5e6f7g...
```

### Exercise 2: Proof of Work

Implementation of Proof of Work consensus mechanism with adjustable mining difficulty.

**Features:**
- Block mining with nonce search
- Adjustable difficulty levels
- Mining time measurement
- Chain validation

**Compilation:**
```bash
cd Exercice_2-PoW
g++ -std=c++14 -o blockchain \
    ../Utils/hash_util.cpp \
    block.cpp \
    blockchain.cpp \
    main.cpp \
    -I../Utils \
    -lssl -lcrypto
```

**Execution:**
```bash
./blockchain
```

**Performance Results:**

| Difficulty | Average Time | Attempts |
|------------|--------------|----------|
| 1          | ~0 ms        | ~16      |
| 2          | ~1 ms        | ~256     |
| 3          | ~16 ms       | ~4,096   |
| 4          | ~128 ms      | ~65,536  |
| 5          | ~4,743 ms    | ~1M      |

### Exercise 3: Proof of Stake

Implementation of Proof of Stake consensus with validator selection.

**Features:**
- Validator registration with stake requirements
- Weighted random validator selection
- Instant block validation (no mining)
- Reward distribution

**Compilation:**
```bash
cd Exercice_3-PoS
g++ -std=c++14 -o pos \
    ../Utils/hash_util.cpp \
    validator.cpp \
    block_pos.cpp \
    blockchain_pos.cpp \
    main.cpp \
    ../Exercice_2-PoW/block.cpp \
    ../Exercice_2-PoW/blockchain.cpp \
    -I../Utils \
    -I../Exercice_2-PoW \
    -lssl -lcrypto
```

**Execution:**
```bash
./pos
```

**Comparison PoW vs PoS:**

| Metric           | PoW          | PoS           | Winner |
|------------------|--------------|---------------|--------|
| Speed            | ~491 ms      | ~0 ms         | PoS    |
| Energy           | High         | Low           | PoS    |
| Security         | High         | Medium        | PoW    |
| Decentralization | High         | Medium        | PoW    |

### Exercise 4: Complete Mini-Blockchain

Full integration of all previous exercises into a complete blockchain system.

**Features:**
- Transaction management with sender, receiver, amount
- Merkle Tree integration for transaction verification
- Support for both PoW and PoS consensus
- Interactive menu for testing different scenarios
- Comprehensive statistics and performance analysis

**Compilation:**
```bash
cd Exercice_4-Mini_Blockchain
g++ -std=c++14 -o mini_blockchain \
    ../Utils/hash_util.cpp \
    ../Exercice_1-Merkle_Tree/merkle_node.cpp \
    ../Exercice_1-Merkle_Tree/merkle_proof.cpp \
    ../Exercice_1-Merkle_Tree/merkle_tree.cpp \
    transaction.cpp \
    validator.cpp \
    block.cpp \
    blockchain.cpp \
    main.cpp \
    -I../Utils \
    -I../Exercice_1-Merkle_Tree \
    -lssl -lcrypto
```

**Execution:**
```bash
./mini_blockchain
```

**Interactive Menu:**
```
+-----------------------------------------------------------+
|                         MENU                              |
+-----------------------------------------------------------+
| 1. Part 1: Block and Chain Structure                     |
| 2. Part 2: Proof of Work (PoW)                           |
| 3. Part 3: Proof of Stake (PoS)                          |
| 4. Part 4: Comparative Analysis                          |
| 5. Execute ALL                                           |
| 0. Exit                                                  |
+-----------------------------------------------------------+
```

## Compilation

### Quick Compile All Exercises

```bash
# Exercise 1
cd Exercice_1-Merkle_Tree && \
g++ -std=c++14 -o merkle ../Utils/hash_util.cpp *.cpp -I../Utils -lssl -lcrypto && \
cd ..

# Exercise 2
cd Exercice_2-PoW && \
g++ -std=c++14 -o blockchain ../Utils/hash_util.cpp *.cpp -I../Utils -lssl -lcrypto && \
cd ..

# Exercise 3
cd Exercice_3-PoS && \
g++ -std=c++14 -o pos ../Utils/hash_util.cpp validator.cpp block_pos.cpp blockchain_pos.cpp main.cpp \
    ../Exercice_2-PoW/block.cpp ../Exercice_2-PoW/blockchain.cpp \
    -I../Utils -I../Exercice_2-PoW -lssl -lcrypto && \
cd ..

# Exercise 4
cd Exercice_4-Mini_Blockchain && \
g++ -std=c++14 -o mini_blockchain \
    ../Utils/hash_util.cpp \
    ../Exercice_1-Merkle_Tree/merkle_node.cpp \
    ../Exercice_1-Merkle_Tree/merkle_proof.cpp \
    ../Exercice_1-Merkle_Tree/merkle_tree.cpp \
    *.cpp \
    -I../Utils -I../Exercice_1-Merkle_Tree -lssl -lcrypto && \
cd ..
```

## Usage

### Example: Creating a Blockchain with PoW

```cpp
#include "blockchain.h"

int main() {
    // Create blockchain with difficulty 4
    Blockchain blockchain(4);
    
    // Add blocks
    std::vector<std::string> tx1 = {"Alice -> Bob: 10 BTC"};
    blockchain.addBlock(tx1);
    
    // Verify chain
    if(blockchain.isValid()) {
        std::cout << "Blockchain is valid!" << std::endl;
    }
    
    // Display blockchain
    blockchain.print();
    
    return 0;
}
```

### Example: Creating a Blockchain with PoS

```cpp
#include "blockchain_pos.h"

int main() {
    BlockchainPoS blockchain;
    
    // Add validators
    blockchain.addValidator("Alice", 100.0);
    blockchain.addValidator("Bob", 50.0);
    
    // Add block (validator selected automatically)
    std::vector<std::string> tx = {"TX1"};
    blockchain.addBlock(tx);
    
    blockchain.print();
    
    return 0;
}
```

## Features

### Core Components

1. **Hash Utilities**
   - SHA-256 hashing using OpenSSL
   - Used for all cryptographic operations

2. **Merkle Tree**
   - Efficient transaction verification
   - O(log n) proof size
   - Tamper-evident structure

3. **Block Structure**
   - Index, timestamp, previous hash
   - Merkle root of transactions
   - Consensus-specific fields (nonce for PoW, validator for PoS)

4. **Blockchain**
   - Genesis block creation
   - Block addition with validation
   - Chain integrity verification

5. **Consensus Mechanisms**
   - **PoW**: Mining with adjustable difficulty
   - **PoS**: Stake-weighted validator selection

### Advanced Features

- Transaction management system
- Validator rewards in PoS
- Performance metrics and statistics
- Comparative analysis tools
- Interactive testing interface

## Performance Comparison

### Speed Analysis (5 blocks)

| Consensus | Total Time | Avg/Block | Speedup |
|-----------|------------|-----------|---------|
| PoW (D=4) | ~2,450 ms  | ~490 ms   | 1x      |
| PoS       | ~2 ms      | ~0.4 ms   | ~1,225x |

### Resource Consumption

- **PoW**: 100% CPU during mining, high energy consumption
- **PoS**: <1% CPU, minimal energy consumption (~1000x less)

### Security Model

- **PoW**: Secured by computational cost (51% attack requires massive hardware)
- **PoS**: Secured by economic stake (validators risk losing staked funds)

### Decentralization

- **PoW**: Highly decentralized (anyone can mine)
- **PoS**: Moderately decentralized (requires minimum stake)

## Key Concepts Demonstrated

1. **Cryptographic Hashing**: SHA-256 for block and transaction integrity
2. **Data Structures**: Merkle Trees for efficient verification
3. **Consensus Algorithms**: Both PoW and PoS implementations
4. **Chain Validation**: Ensuring blockchain integrity
5. **Performance Analysis**: Real-world timing comparisons

## Troubleshooting

### Common Issues

**Issue**: `fatal error: openssl/sha.h: No such file or directory`
**Solution**: Install OpenSSL development libraries
```bash
sudo apt-get install libssl-dev
```

**Issue**: `undefined reference to SHA256`
**Solution**: Add `-lssl -lcrypto` to compilation flags

**Issue**: Compilation errors with C++17 features
**Solution**: Use `-std=c++14` flag and ensure structured bindings are replaced with iterators

## Educational Value

This project demonstrates:

- Object-oriented design in C++
- Cryptographic primitives usage
- Data structure implementation (trees)
- Algorithm complexity analysis
- Performance benchmarking
- Consensus mechanism design

## Future Enhancements

Potential additions:
- Network communication between nodes
- Transaction signature verification
- Smart contract support
- Persistent storage (database integration)
- Mining pool implementation
- Wallet functionality
- API for external interaction

## Contributing

Contributions are welcome! Please follow these guidelines:

1. Fork the repository
2. Create a feature branch
3. Commit your changes with clear messages
4. Add tests for new functionality
5. Submit a pull request

## License

This project is created for educational purposes.

## Authors

Created as part of blockchain technology coursework.

## Acknowledgments

- OpenSSL library for cryptographic functions
- Bitcoin and Ethereum for consensus mechanism inspiration
- Academic resources on blockchain technology