#include "transaction.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Transaction::Transaction(const std::string& id,
                         const std::string& sender,
                         const std::string& receiver,
                         double amount)
    : id_(id), sender_(sender), receiver_(receiver), amount_(amount) {}

std::string Transaction::toString() const {
    std::stringstream ss;
    ss << sender_ << " -> " << receiver_ << ": " << std::fixed 
       << std::setprecision(2) << amount_ << " BTC";
    return ss.str();
}

std::string Transaction::toHash() const {
    std::stringstream ss;
    ss << id_ << sender_ << receiver_ << amount_;
    return ss.str();
}

void Transaction::print() const {
    std::cout << "  [" << id_ << "] " << toString() << std::endl;
}
