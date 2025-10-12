#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
private:
    std::string address_;
    double stake_;
    int blocksValidated_;

public:
    Validator();  // ← Constructeur par défaut ajouté
    Validator(const std::string& address, double stake);
    
    const std::string& getAddress() const { return address_; }
    double getStake() const { return stake_; }
    int getBlocksValidated() const { return blocksValidated_; }
    
    void addStake(double amount);
    void incrementBlocksValidated();
    void print() const;
};

#endif