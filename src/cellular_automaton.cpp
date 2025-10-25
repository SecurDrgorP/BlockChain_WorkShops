#include "cellular_automaton.h"
#include "utils.h"
#include "sha256.h" // <-- IMPORTANT: Include sha256 for pre-hashing
#include <iostream>

// (Constructor, evolve, printState, getState implementations remain the same...)

CellularAutomaton::CellularAutomaton(uint8_t rule, const std::vector<int>& initial_state)
    : rule_(rule), state_(initial_state) {}

void CellularAutomaton::evolve() {
    if (state_.empty()) return;
    std::vector<int> next_state(state_.size());
    for (size_t i = 0; i < state_.size(); ++i) {
        int left = (i == 0) ? 0 : state_[i - 1];
        int center = state_[i];
        int right = (i == state_.size() - 1) ? 0 : state_[i + 1];
        int index = (left << 2) | (center << 1) | right;
        next_state[i] = (rule_ >> index) & 1;
    }
    state_ = next_state;
}

const std::vector<int>& CellularAutomaton::getState() const { return state_; }
void CellularAutomaton::printState() const { /* ... */ }

// --- ROBUST Hashing Function Implementation ---

std::string ac_hash(const std::string& input, uint8_t rule, size_t steps) {
    // --- THE DEFINITIVE FIX: Pre-hashing ---
    // 1. Create a pre-hashed input to guarantee high diffusion.
    // A 1-bit change in 'input' now creates a ~128-bit change in 'pre_hashed_input'.
    std::string pre_hashed_input = input + sha256(input);

    // 2. Convert the diffused input to bits.
    std::vector<int> initial_state = string_to_bits(pre_hashed_input);

    // Ensure the state is wide enough.
    while (initial_state.size() < 512) {
        initial_state.insert(initial_state.end(), initial_state.begin(), initial_state.end());
    }

    CellularAutomaton automaton(rule, initial_state);

    // 3. Evolve the automaton.
    for (size_t i = 0; i < steps; ++i) {
        automaton.evolve();
    }

    std::vector<int> final_state = automaton.getState();
    std::vector<int> hash_bits;

    // 4. Sample from the center.
    size_t center = final_state.size() / 2;
    size_t start_index = center - 128;
    for (size_t i = 0; i < 256; ++i) {
        hash_bits.push_back(final_state[start_index + i]);
    }

    return bits_to_hex_string(hash_bits);
}
