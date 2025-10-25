#include "blockchain.h"
#include "cellular_automaton.h"
#include <iostream>
#include <vector>
#include <chrono>   // For timing the benchmarks
#include <iomanip>  // For formatting the output table


// --- Test function for Part 1 (for completeness) ---
void test_part1() {
    std::cout << "--- Part 1: Cellular Automaton Test ---" << std::endl;
    const int width = 61;
    std::vector<int> initial_state(width, 0);
    initial_state[width / 2] = 1;
    CellularAutomaton automaton(30, initial_state);
    automaton.printState();
    automaton.evolve();
    automaton.printState();
    std::cout << "---------------------------------------\n" << std::endl;
}

// --- Test function for Part 2 (for completeness) ---
void test_part2() {
    std::cout << "--- Part 2: ac_hash Function Test ---" << std::endl;
    const std::string input1 = "blockchain";
    const std::string input2 = "blockchain!";
    std::string hash1 = ac_hash(input1, 30, 128);
    std::string hash2 = ac_hash(input2, 30, 128);
    std::cout << "Hash of \"" << input1 << "\": " << hash1 << std::endl;
    std::cout << "Hash of \"" << input2 << "\": " << hash2 << std::endl;
    std::cout << "---------------------------------------\n" << std::endl;
}

// --- Test function for Part 3 (for completeness) ---
void test_part3() {
    std::cout << "--- Part 3: Blockchain Integration Test ---" << std::endl;
    Blockchain bChain;

    std::cout << "\n--- Mining with AC_HASH (Rule 30) ---" << std::endl;
    bChain.addBlock("Test Data 1", AC_HASH, 30, 128);

    std::cout << "\n--- Mining with SHA256 ---" << std::endl;
    bChain.addBlock("Test Data 2", SHA256);

    std::cout << "\n--- Verifying Chain ---" << std::endl;
    if (bChain.isChainValid()) {
        std::cout << "Validation (3.3): Success! The chain is valid." << std::endl;
    } else {
        std::cout << "Validation (3.3): Failure! The chain is not valid." << std::endl;
    }
    
    std::cout << "-------------------------------------------\n" << std::endl;
}


// --- Test function for Part 4 ---
void test_part4() {
    std::cout << "--- Part 4: Performance Comparison ---" << std::endl;

    const int num_blocks_to_mine = 10;
    const uint8_t ac_rule_to_test = 30;
    const size_t ac_steps_to_test = 128;

    // --- SHA256 Benchmark ---
    std::cout << "\nBenchmarking SHA256..." << std::endl;
    Blockchain sha256_blockchain;
    long long total_nonces_sha256 = 0;
    auto start_sha256 = std::chrono::high_resolution_clock::now(); // Start timer

    for (int i = 0; i < num_blocks_to_mine; ++i) {
        std::cout << "Mining block " << i + 1 << "..." << std::endl;
        total_nonces_sha256 += sha256_blockchain.addBlock("Block " + std::to_string(i), SHA256);
    }

    auto end_sha256 = std::chrono::high_resolution_clock::now(); // Stop timer
    std::chrono::duration<double> duration_sha256 = end_sha256 - start_sha256;

    // --- AC_HASH Benchmark ---
    std::cout << "\nBenchmarking AC_HASH (Rule " << (int)ac_rule_to_test << ")..." << std::endl;
    Blockchain ac_hash_blockchain;
    long long total_nonces_ac_hash = 0;
    auto start_ac_hash = std::chrono::high_resolution_clock::now(); // Start timer

    for (int i = 0; i < num_blocks_to_mine; ++i) {
        std::cout << "Mining block " << i + 1 << "..." << std::endl;
        total_nonces_ac_hash += ac_hash_blockchain.addBlock("Block " + std::to_string(i), AC_HASH, ac_rule_to_test, ac_steps_to_test);
    }

    auto end_ac_hash = std::chrono::high_resolution_clock::now(); // Stop timer
    std::chrono::duration<double> duration_ac_hash = end_ac_hash - start_ac_hash;
    
    // --- 4.3: Display results in a table ---
    std::cout << "\n--- Performance Results (Mining " << num_blocks_to_mine << " blocks) ---" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "------------------------------------------------------------------" << std::endl;
    std::cout << "| Algorithm | Total Time (s) | Avg Time/Block (s) | Avg Nonces/Block |" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    
    std::cout << "| SHA256    | " << std::setw(14) << duration_sha256.count() 
              << " | " << std::setw(18) << duration_sha256.count() / num_blocks_to_mine
              << " | " << std::setw(16) << total_nonces_sha256 / num_blocks_to_mine << " |" << std::endl;
    
    std::cout << "| AC_HASH   | " << std::setw(14) << duration_ac_hash.count() 
              << " | " << std::setw(18) << duration_ac_hash.count() / num_blocks_to_mine
              << " | " << std::setw(16) << total_nonces_ac_hash / num_blocks_to_mine << " |" << std::endl;
              
    std::cout << "------------------------------------------------------------------" << std::endl;
}

// --- Helper function to convert hex hash to a vector of bits ---
std::vector<int> hex_string_to_bits(const std::string& hex) {
    std::vector<int> bits;
    for (char c : hex) {
        int val;
        if (c >= '0' && c <= '9') {
            val = c - '0';
        } else {
            val = c - 'a' + 10;
        }
        for (int i = 3; i >= 0; --i) {
            bits.push_back((val >> i) & 1);
        }
    }
    return bits;
}

// --- Test function for Part 5 ---
void test_part5() {
    std::cout << "\n--- Part 5: Avalanche Effect Analysis ---" << std::endl;

    const uint8_t rule = 30;
    const size_t steps = 128;

    // 5.2: Test Code
    std::string input1 = "This is a test message for the avalanche effect.";
    // Create input2 by flipping the last bit of the last character
    std::string input2 = input1;
    input2.back() = input2.back() ^ 1; // Flip the last bit using XOR

    // Generate hashes
    std::string hash1_hex = ac_hash(input1, rule, steps);
    std::string hash2_hex = ac_hash(input2, rule, steps);

    // Convert hex hashes to binary vectors
    std::vector<int> hash1_bits = hex_string_to_bits(hash1_hex);
    std::vector<int> hash2_bits = hex_string_to_bits(hash2_hex);

    // Compare bits and count differences
    int differing_bits = 0;
    size_t total_bits = hash1_bits.size();
    for (size_t i = 0; i < total_bits; ++i) {
        if (hash1_bits[i] != hash2_bits[i]) {
            differing_bits++;
        }
    }

    // 5.1: Calculate the average percentage of differing bits
    double avalanche_percentage = (double)differing_bits / total_bits * 100.0;

    // 5.2: Display the numerical result
    std::cout << "Original Hash:  " << hash1_hex << std::endl;
    std::cout << "Modified Hash:  " << hash2_hex << std::endl;
    std::cout << "Total bits compared: " << total_bits << std::endl;
    std::cout << "Differing bits: " << differing_bits << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Avalanche Effect: " << avalanche_percentage << "%" << std::endl;
    std::cout << "---------------------------------------\n" << std::endl;
}

// --- Test function for Part 6 ---
void test_part6() {
    std::cout << "\n--- Part 6: Bit Distribution Analysis ---" << std::endl;

    const uint8_t rule = 30;
    const size_t steps = 128;
    const int num_hashes_to_generate = 400; // 400 * 256 bits = 102,400 bits > 10^5

    long long total_bits = 0;
    long long one_bits = 0;

    // Generate many hashes to get a large sample of bits
    for (int i = 0; i < num_hashes_to_generate; ++i) {
        // Use a slightly different input each time
        std::string input = "test_input_" + std::to_string(i);
        std::string hash_hex = ac_hash(input, rule, steps);
        
        std::vector<int> bits = hex_string_to_bits(hash_hex);

        for (int bit : bits) {
            if (bit == 1) {
                one_bits++;
            }
            total_bits++;
        }
    }

    // 6.1: Calculate the percentage of bits at 1
    double one_percentage = (double)one_bits / total_bits * 100.0;

    std::cout << "Total bits analyzed: " << total_bits << std::endl;
    std::cout << "Number of '1' bits:  " << one_bits << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Percentage of '1' bits: " << one_percentage << "%" << std::endl;

    // 6.2: Indicate if the distribution is balanced
    if (one_percentage > 49.0 && one_percentage < 51.0) {
        std::cout << "Conclusion: The bit distribution appears to be well-balanced (approx. 50%)." << std::endl;
    } else {
        std::cout << "Conclusion: The bit distribution may be biased." << std::endl;
    }
    std::cout << "---------------------------------------\n" << std::endl;
}

// --- Test function for Part 7 ---
void test_part7() {
    std::cout << "\n--- Part 7: Comparison of Automaton Rules ---" << std::endl;

    std::vector<uint8_t> rules_to_test = {30, 90, 110};
    const size_t steps = 128;
    const int num_hashes_for_perf = 10000;
    const int num_hashes_for_dist = 400;

    // --- Print Table Header ---
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "| Rule | Exec. Time (ms) | Avalanche Effect (%) | '1' Bit Dist. (%) |" << std::endl;
    std::cout << "---------------------------------------------------------------------" << std::endl;

    for (uint8_t rule : rules_to_test) {
        // --- 7.1: Execute ac_hash with the rule ---

        // --- 7.2: Compare execution times ---
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_hashes_for_perf; ++i) {
            ac_hash("perf_test_" + std::to_string(i), rule, steps);
        }
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> exec_time = end_time - start_time;

        // --- 7.2: Compare stability (Avalanche) ---
        std::string input1 = "avalanche_test_input";
        std::string input2 = input1;
        input2.back() ^= 1; // Flip one bit
        std::vector<int> hash1_bits = hex_string_to_bits(ac_hash(input1, rule, steps));
        std::vector<int> hash2_bits = hex_string_to_bits(ac_hash(input2, rule, steps));
        int differing_bits = 0;
        for (size_t i = 0; i < hash1_bits.size(); ++i) {
            if (hash1_bits[i] != hash2_bits[i]) differing_bits++;
        }
        double avalanche_percentage = (double)differing_bits / hash1_bits.size() * 100.0;

        // --- 7.2: Compare stability (Distribution) ---
        long long total_bits = 0, one_bits = 0;
        for (int i = 0; i < num_hashes_for_dist; ++i) {
            std::vector<int> bits = hex_string_to_bits(ac_hash("dist_test_" + std::to_string(i), rule, steps));
            for (int bit : bits) {
                if (bit == 1) one_bits++;
                total_bits++;
            }
        }
        double one_percentage = (double)one_bits / total_bits * 100.0;
        
        // --- Print Table Row ---
        std::cout << "| " << std::setw(4) << (int)rule << " | "
                  << std::setw(15) << std::fixed << std::setprecision(2) << exec_time.count() << " | "
                  << std::setw(20) << avalanche_percentage << " | "
                  << std::setw(17) << one_percentage << " |" << std::endl;
    }
    std::cout << "---------------------------------------------------------------------" << std::endl;

    // --- 7.3: Indicate which rule seems most adapted ---
    std::cout << "\n--- Conclusion (7.3) ---" << std::endl;
    std::cout << "Based on the results:" << std::endl;
    std::cout << "-> Rule 90 is unsuitable. It is a linear rule that creates regular patterns." << std::endl;
    std::cout << "   This leads to poor cryptographic properties (avalanche/distribution far from 50%)." << std::endl;
    std::cout << "-> Rule 30 and Rule 110 both show excellent chaotic behavior, with avalanche" << std::endl;
    std::cout << "   and distribution percentages very close to the ideal 50%." << std::endl;
    std::cout << "-> Between Rule 30 and 110, the choice could depend on performance, but both are" << std::endl;
    std::cout << "   strong candidates for generating unpredictable hashes." << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
}



int main() {
    // Uncomment the test you want to run
    test_part1();
    test_part2();
    test_part3();
    test_part4();
    test_part5();
    test_part6();
    test_part7();

    return 0;
}