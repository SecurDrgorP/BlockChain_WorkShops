#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
private:
    std::string address_;
    double stake_;
    int blocksValidated_;
    double rewardsEarned_;

public:
    Validator();
    Validator(const std::string& address, double stake);
    
    const std::string& getAddress() const { return address_; }
    double getStake() const { return stake_; }
    int getBlocksValidated() const { return blocksValidated_; }
    double getRewardsEarned() const { return rewardsEarned_; }
    
    void incrementBlocksValidated();
    void addReward(double reward);
    void print() const;
};

#endif