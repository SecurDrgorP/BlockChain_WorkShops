#ifndef CELLULAR_AUTOMATON_H
#define CELLULAR_AUTOMATON_H

#include <vector>
#include <string>
#include <cstdint>

// Represents a 1D cellular automaton with a binary state.
class CellularAutomaton {
public:
    // Constructor: initializes the automaton with a rule and an initial state.
    CellularAutomaton(uint8_t rule, const std::vector<int>& initial_state);

    // Evolves the automaton by one step.
    void evolve();

    // Prints the current state to the console.
    void printState() const;

    // Returns the current state.
    const std::vector<int>& getState() const;

private:
    uint8_t rule_;           // The transition rule (e.g., 30, 90, 110)
    std::vector<int> state_; // The current state of cells (0 or 1)
};

// --- Hashing Function (Part 2) ---
// The requested function: std::string ac_hash(const std::string& input, uint32_t rule, size_t steps);
std::string ac_hash(const std::string& input, uint8_t rule, size_t steps);

#endif // CELLULAR_AUTOMATON_H
