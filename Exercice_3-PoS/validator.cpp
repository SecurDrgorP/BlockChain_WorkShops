#include "validator.h"
#include <iostream>

Validator::Validator() : address_(""), stake_(0.0), blocksValidated_(0) {}

Validator::Validator(const std::string& address, double stake)
    : address_(address), stake_(stake), blocksValidated_(0) {}

void Validator::addStake(double amount) {
    stake_ += amount;
}

void Validator::incrementBlocksValidated() {
    blocksValidated_++;
}

void Validator::print() const {
    std::cout << "┌────────────────────────────────────┐\n";
    std::cout << "│ Validator: " << address_ << "\n";
    std::cout << "├────────────────────────────────────┤\n";
    std::cout << "│ Stake: " << stake_ << " ETH\n";
    std::cout << "│ Blocks Validated: " << blocksValidated_ << "\n";
    std::cout << "└────────────────────────────────────┘\n";
}