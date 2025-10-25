# BlockChain_WorkShops
# Cellular Automaton Hashing in a Blockchain

## Project Overview

This project, developed for the Master IASD 2025/2026 Blockchain module under Pr. Ikram BENABDELOUAHAB, implements a custom hash function based on 1D Cellular Automata and integrates it into a proof-of-concept blockchain. The implementation compares CA-based hashing against SHA-256 to evaluate its cryptographic properties and performance.

## Project Structure

```
.
├── bin/                      # Compiled executables
├── include/                  # Header files (.h)
│   ├── blockchain.h
│   ├── cellular_automaton.h
│   ├── sha256.h
│   └── utils.h
├── src/                      # Source files (.cpp)
│   ├── blockchain.cpp
│   ├── cellular_automaton.cpp
│   ├── main.cpp
│   ├── sha256.cpp
│   └── utils.cpp
├── Makefile
└── README.md
```

## Installation and Build

**Prerequisites:** C++11 compiler, OpenSSL library

```bash
# Install dependencies like openSSL if not installed in your machine

# Compile
make

# Run
make run

# Clean
make clean
```

## Core Features

- **Cellular Automaton Engine:** 1D CA supporting Wolfram rules (30, 90, 110)
- **ac_hash Function:** Custom 256-bit hash function based on CA evolution
- **Blockchain Integration:** Proof-of-work mining with both SHA-256 and AC_HASH
- **Comprehensive Testing:** Performance, avalanche effect, bit distribution, and rule comparison

## Experimental Results

### Hash Function Verification
```
Hash("blockchain"):  3157372f7b2673b67ee0709e7f2f2d0f699d07cb62f5b93e182c6484c19e877b
Hash("blockchain!"): 53af4389324e01bb28d11a59e648a107533f8ea11d58c72e2262b1bd654c02cf
```
Single character change produces completely different hash.

### Performance Comparison (10 blocks, difficulty=4)

| Algorithm | Total Time (s) | Avg Time/Block (s) | Avg Nonces |
|-----------|----------------|-------------------|------------|
| SHA256    | 1.8513        | 0.1851            | 65,711     |
| AC_HASH   | 0.0348        | 0.0035            | 1          |

**Critical Finding:** The extremely low nonce count for AC_HASH indicates structural bias in the hash function. This makes mining trivially easy but represents a security vulnerability, not an advantage.

### Avalanche Effect Analysis
```
Single bit flip in input
Differing bits: 106/256 (41.41%)
```
**Result:** Acceptable avalanche effect (target: ~50%, acceptable range: 40-60%)

### Bit Distribution
```
Total bits analyzed: 102,400
'1' bits: 51,078 (49.88%)
```
**Result:** Nearly perfect bit balance.

### Rule Comparison

| Rule | Execution Time (ms) | Avalanche (%) | Bit Distribution (%) |
|------|-------------------|---------------|---------------------|
| 30   | 11,381           | 51.56         | 50.10               |
| 90   | 11,906           | 35.55         | 33.19               |
| 110  | 11,724           | 50.78         | 56.93               |

**Conclusion:**
- **Rule 30:** Best choice - excellent avalanche and distribution, fastest execution
- **Rule 90:** Unsuitable - linear rule creates predictable patterns
- **Rule 110:** Acceptable but slightly biased distribution

## Analysis and Conclusions

### Question 8: Advantages of CA-Based Hashing

1. **Simplicity:** Based on basic bitwise operations, easy to implement and audit
2. **Parallelization:** Each cell computed independently, ideal for GPU/FPGA
3. **ASIC Resistance:** Non-standard algorithm lacks specialized hardware
4. **Tunable Security:** Adjustable rules and evolution steps
5. **Novel Approach:** Alternative to number-theoretic functions, potential quantum resistance

### Question 9: Weaknesses Discovered

1. **Poor Initial Diffusion:** Minor input changes failed to propagate without pre-processing
2. **Structural Bias:** Limited output patterns make it unsuitable for standard Proof-of-Work
   - Expected nonces: ~65,000
   - Actual nonces: ~1 (indicates bias toward certain hash prefixes)
3. **Lack of Cryptanalysis:** No peer review or security proofs unlike SHA-256
4. **Implementation Sensitivity:** Small design choices dramatically affect security

### Question 10: Proposed Improvements

**1. Hybrid Approach (Recommended)**
```cpp
// Pre-hashing variant (implemented)
string hybrid_hash(const string& input) {
    return ac_hash(input + sha256(input), 30, 256);
}

// Post-hashing variant
string hybrid_hash_v2(const string& input) {
    return sha256(ac_hash(input, 30, 256));
}
```
Combines SHA-256 security with CA complexity and ASIC resistance.

**2. Multi-Rule Ensemble**
```cpp
string ensemble_hash(const string& input) {
    string h30 = ac_hash(input, 30, 85);
    string h90 = ac_hash(input, 90, 85);
    string h110 = ac_hash(input, 110, 86);
    return xor_combine(h30, h90, h110);
}
```
Distributes security across multiple rules.

**3. Dynamic Rule Selection**
Select rule based on input characteristics to prevent optimization attacks.

**4. Enhanced State Mixing**
XOR multiple evolution snapshots to increase dependence on computation history.

**5. 2D Cellular Automaton**
Extend to 16x16 grid for richer neighborhood interactions and better mixing.

## Final Recommendations

**Best Configuration:**
- Rule: 30 (optimal cryptographic properties)
- State size: 256 bits
- Evolution steps: 256
- Mode: Hybrid (CA + SHA-256)

**Key Insight:** Pure CA hashing has fundamental flaws for blockchain Proof-of-Work. The hybrid approach combining CA with SHA-256 is the most viable path to production readiness, offering proven security plus ASIC resistance.

**Verdict:** CA-based hashing is a valuable research direction but requires hybrid design with established hash functions for real-world deployment.

---

**Note:** This is an educational proof-of-concept. Not suitable for production without extensive cryptographic auditing.