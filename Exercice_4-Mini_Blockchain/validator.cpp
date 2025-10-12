#include "validator.h"
#include <iostream>
#include <iomanip>

Validator::Validator() 
    : address_(""), stake_(0.0), blocksValidated_(0), rewardsEarned_(0.0) {}

Validator::Validator(const std::string& address, double stake)
    : address_(address), stake_(stake), blocksValidated_(0), rewardsEarned_(0.0) {}

void Validator::incrementBlocksValidated() {
    blocksValidated_++;
}

void Validator::addReward(double reward) {
    rewardsEarned_ += reward;
}

void Validator::print() const {
    std::cout << "  " << std::setw(10) << std::left << address_ 
              << " | Stake: " << std::setw(7) << std::fixed << std::setprecision(2) << stake_ << " ETH"
              << " | Blocks: " << std::setw(3) << blocksValidated_
              << " | Rewards: " << std::fixed << std::setprecision(4) << rewardsEarned_ << " ETH" << std::endl;
}